
#include <Windows.h>
#include <stdio.h>

#include <math.h>

#define inline

#include <libavutil/opt.h>
#include <libavcodec/avcodec.h>
#include <libavutil/channel_layout.h>
#include <libavutil/common.h>
#include <libavutil/imgutils.h>
#include <libavutil/mathematics.h>
#include <libavutil/samplefmt.h>
#include <libavformat/avformat.h>
#include <libavformat/avio.h>
#include <libavutil/file.h>
#include <libavdevice/avdevice.h>
#include <libswscale/swscale.h>

#include "ip.h"

DWORD t_start;

extern void show_image(int h, int w, unsigned char *data);

struct buffer_data 
{
	uint8_t *ptr;
	size_t size; ///< size left in the buffer
};



int process_frames(int videoStreamIdx , AVFormatContext *pFormatCtx , AVCodecContext  *pCodecCtx , AVCodec *pCodec)
{
	static int		frames=0;
	int             y, i;
	AVPacket        packet;
	int             frameFinished;
	enum AVPixelFormat  pFormat = AV_PIX_FMT_BGR24;
	AVFrame        *pFrame;
	AVFrame		   *pFrameRGB;
	unsigned char *buffer;
	struct SwsContext * img_convert_ctx;
	int numBytes = avpicture_get_size(pFormat,pCodecCtx->width,pCodecCtx->height) ; //AV_PIX_FMT_RGB24
	static DWORD t = 0;

	/// Allocate video frame
	pFrame = av_frame_alloc(); //avcodec_alloc_frame();
	pFrameRGB = av_frame_alloc(); //avcodec_alloc_frame();

	buffer = (uint8_t *) av_malloc(numBytes*sizeof(uint8_t));
	avpicture_fill((AVPicture *) pFrameRGB,buffer,pFormat,pCodecCtx->width,pCodecCtx->height);


	if(t==0) t=timeGetTime();
	printf("\n");
	for(i=0; av_read_frame(pFormatCtx, &packet) >= 0;) 
	{

		// Is this a packet from the video stream?
		if(packet.stream_index==videoStreamIdx) 
		{
			i++;

		    packet.pts = AV_NOPTS_VALUE;
			packet.dts = AV_NOPTS_VALUE;
			/// Decode video frame
			avcodec_decode_video2(pCodecCtx, pFrame, &frameFinished, &packet);

			// Did we get a video frame?
			if(frameFinished) 
			{
				frames++;
				//printf("%4d  ",timeGetTime() -t);
				//if((timeGetTime()-t)>70) printf("|"); else printf(".");
				if(timeGetTime()-t>=1000)
				{
					t=timeGetTime();
					printf("%3d ",frames);fflush(stdout);
					frames=0;
				}
				//printf("\rFrame [%5d]: w=%3d, h=%3d, t=%2d, key=%1d, fmt=%2d, pkt_sz=%5d, line_sz=%5d, color_space=%d\n", i, pFrame->width,pFrame->height,pFrame->type,pFrame->key_frame,pFrame->format,pFrame->pkt_size,pFrame->linesize[0],pFrame->colorspace);
				//printf("%5d: %d\n",GetTickCount()-t_start,i);fflush(stdout);
				img_convert_ctx = sws_getCachedContext(NULL,pCodecCtx->width, pCodecCtx->height, pCodecCtx->pix_fmt,   pCodecCtx->width, pCodecCtx->height, AV_PIX_FMT_BGR24, SWS_BICUBIC, NULL, NULL,NULL);
				sws_scale(img_convert_ctx, ((AVPicture*)pFrame)->data, ((AVPicture*)pFrame)->linesize, 0, pCodecCtx->height, ((AVPicture *)pFrameRGB)->data, ((AVPicture *)pFrameRGB)->linesize);

				show_image(pFrame->height, pFrame->width, pFrameRGB->data[0]); 
				sws_freeContext(img_convert_ctx);                // Write pixel data
			}
		}

		// Free the packet that was allocated by av_read_frame
		av_free_packet(&packet);
	}
	printf("\n");

	/// Free the Y frame
	av_free(pFrame);

	return 0;
}



static int read_packet(void *opaque, uint8_t *buf, int buf_size)
{
	static int total=0;
	int result;;

	result=tcp_recv((char*)buf,buf_size,0);
	total+=result;
	printf("%5d: now/toal: %5d / %7d\n", GetTickCount()-t_start,result,total);fflush(stdout);

	return result;
}



int avio_reading_main(int argc, char *argv[])
{
	int             videoStreamIdx;
	AVCodecContext  *pCodecCtx;
	AVCodec         *pCodec;
	AVFormatContext *fmt_ctx = NULL;
	AVIOContext *avio_ctx = NULL;
	AVOption option;
	uint8_t *buffer = NULL, *avio_ctx_buffer = NULL;
	size_t buffer_size, avio_ctx_buffer_size = 16384;
	char *input_filename = NULL;
	int ret = 0;
	int result;

	timeBeginPeriod(1);

	t_start = GetTickCount();

	//tcp_client_init("192.168.2.250",5001);
	//tcp_client_close();
	tcp_client_init("192.168.2.213",5001);
	//tcp_client_init("127.0.0.1",5001);

	/* register codecs and formats and other lavf/lavc components*/
	av_register_all();
	avcodec_register_all();
	avformat_network_init();

	if (!(fmt_ctx = avformat_alloc_context())) 
	{
		ret = AVERROR(ENOMEM);
		goto end;
	}

	fmt_ctx->flags |= AVFMT_FLAG_NOBUFFER;

	result = av_opt_set(fmt_ctx->priv_data,"probesize2","1000",0);
	result = av_opt_set(fmt_ctx->priv_data,"max_analyze_duration","500",0);

	avio_ctx_buffer = (uint8_t*) av_malloc(avio_ctx_buffer_size);
	if (!avio_ctx_buffer) 
	{
		ret = AVERROR(ENOMEM);
		goto end;
	}
	avio_ctx = avio_alloc_context(avio_ctx_buffer, avio_ctx_buffer_size, 0, NULL, &read_packet, NULL, NULL);
	if (!avio_ctx) 
	{
		ret = AVERROR(ENOMEM);
		goto end;
	}
	fmt_ctx->pb = avio_ctx;

	ret = avformat_open_input(&fmt_ctx, NULL, NULL, NULL);
	if (ret < 0) 
	{
		fprintf(stderr, "Could not open input\n");
		goto end;
	}

	ret = avformat_find_stream_info(fmt_ctx, NULL);
	if (ret < 0) 
	{
		fprintf(stderr, "Could not find stream information\n");
		goto end;
	}

	av_dump_format(fmt_ctx, 0, input_filename, 0);

	/// Find the first video stream
	{
		int i = 0;
		videoStreamIdx=-1;
		for(i=0; 2; i++)
		{
			if(fmt_ctx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO) 
			{ //CODEC_TYPE_VIDEO
				videoStreamIdx=i;
				break;
			}
		}
	}
	/// Check if video stream is found
	if(videoStreamIdx==-1) 	return -1; // Didn't find a video stream

	/// Get a pointer to the codec context for the video stream
	pCodecCtx = fmt_ctx->streams[videoStreamIdx]->codec;

	/// Find the decoder for the video stream
	pCodec = avcodec_find_decoder( pCodecCtx->codec_id);
	if(pCodec==NULL) 
	{
		fprintf(stderr, "Unsupported codec!\n");
		return -1; // Codec not found
	}

	//avcodec_get_context_defaults3(pCodecCtx, pCodec);
	pCodecCtx->flags |= CODEC_FLAG_LOW_DELAY;
	pCodecCtx->flags2 |= CODEC_FLAG2_CHUNKS;
	pCodecCtx->thread_count = 2;
	pCodecCtx->thread_type = FF_THREAD_SLICE;
	pCodecCtx->strict_std_compliance = FF_COMPLIANCE_EXPERIMENTAL;

	/// Open codec
	if( avcodec_open2(pCodecCtx, pCodec, NULL) < 0 )	return -1; // Could not open codec

	process_frames(videoStreamIdx, fmt_ctx, pCodecCtx, pCodec);

	/// Close the codec
	avcodec_close(pCodecCtx);

end:
	avformat_close_input(&fmt_ctx);
	/* note: the internal buffer could have changed, and be != avio_ctx_buffer */
	if (avio_ctx) 
	{
		av_freep(&avio_ctx->buffer);
		av_freep(&avio_ctx);
	}

	return 0;
}






#if 0
void test(void)
{
	AVCodec * codec;
	AVCodecContext *context;
	AVFrame *frame;
    AVPacket packet;
    int got_frame = 0;
	int result, total;
	char data[4000];
	int len;
	int i;

	av_register_all();
	avcodec_register_all();
	avformat_network_init();

	codec = avcodec_find_decoder(AV_CODEC_ID_H264);
	if (!codec) 
	{
		fprintf(stderr, "Codec not found\n");
		exit(1);
	}

	context = avcodec_alloc_context3(codec);
	if (!context)
	{
		fprintf(stderr, "Could not allocate video codec context\n");
		exit(1);
	}
	avcodec_get_context_defaults3(context, codec);
	context->flags |= CODEC_FLAG_LOW_DELAY;
	context->flags2 |= CODEC_FLAG2_CHUNKS;
	context->thread_count = 4;
	context->thread_type = FF_THREAD_SLICE;
	context->strict_std_compliance = FF_COMPLIANCE_EXPERIMENTAL;
	if (avcodec_open2(context, codec, NULL) < 0)
	{
		fprintf(stderr, "Could not open codec\n");
		exit(1);
	}

	frame = av_frame_alloc();
	if (!frame) 
	{
		fprintf(stderr, "Could not allocate video frame\n");
		exit(1);
	}

	total=0;
	i=0;
    av_init_packet(&packet);
    packet.pts = AV_NOPTS_VALUE;
    packet.dts = AV_NOPTS_VALUE;
    packet.data = (uint8_t*) data;//your frame data
	while((result=tcp_recv((char*)data,2000,0))>0)
	{
		total+=result;
		printf("%5d: total bytes read so far:%7d\n", GetTickCount()-t_start,total);fflush(stdout);
        packet.size = result;//your frame data size
        len = avcodec_decode_video2(context, frame, &got_frame, &packet);
        if (len >= 0 && got_frame)
        {
			i++;
			//do things with the data, like converting it to RGB, resizing it etc.
			printf("\rFrame [%5d]: w=%3d, h=%3d, t=%2d, key=%1d, fmt=%2d, pkt_sz=%5d, line_sz=%5d, color_space=%d\n", i, frame->width,frame->height,frame->type,frame->key_frame,frame->format,frame->pkt_size,frame->linesize[0],frame->colorspace);
        }
	}
}
#endif



#if 0
void convertFFmpeg()
{
	AVFrame* src;//input FFmpeg (with decoded data)
	AVFrame* dst;//output with OpenCV compatible data
	SwsContext* modifContext;
	modifContext = sws_getContext(src->width,
		src->height,
		(enum AVPixelFormat) src->format,
		dst->width,
		dst->height,
		PIX_FMT_BGR24,//OpenCV compatible format
		/*
		* Modifiation algo.
		* List in swscale.h
		*/
		SWS_BICUBIC,
		NULL, NULL, NULL);

	sws_scale(modifContext,
		src->data,//input FFMpeg
		src->linesize,
		0,//image entirely modify
		src->height,
		dst->data,//sortie RGB24 compatible OpenCV
		dst->linesize);

}
#endif

