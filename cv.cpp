
#include <sstream>
#include <string>
#include <iostream>
#include <stdio.h>

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

/*
ilmimf.lib;zlib.lib;libjasper.lib;libpng.lib;libtiff.lib;libjpeg.lib;opencv_photo249.lib;opencv_features2d249.lib;opencv_gpu249.lib;opencv_objdetect249.lib;opencv_video249.lib;opencv_videostab249.lib;opencv_legacy249.lib;opencv_flann249.lib;opencv_contrib249.lib;opencv_core249.lib;opencv_highgui249.lib;opencv_imgproc249.lib;Comctl32.lib;Vfw32.lib;
*/

using namespace std;
using namespace cv;

VideoCapture capture;
Mat img[10];
Mat img_temp;
double t;
int skip=0, skipped=0;
RNG rng(12345);

unsigned short rgb565_img[320*240];
unsigned short hsv_lut[65536];
unsigned char out1[320*240];
unsigned char out2[320*240];

typedef struct
{
	double min;
	double avg;
	double max;
} t_times;

t_times times[1000];

int cv_loop(void);

#ifdef WIN32
#define PRINT_TIMES 0
#else
#define PRINT_TIMES 1
#endif

#define T(e) \
	t = (double)getTickCount(); \
	e; \
	t = (((double)getTickCount()-t)/(double)getTickFrequency())*1000.0; \
	if(times[__LINE__].avg==0.0) times[__LINE__].avg=t; else times[__LINE__].avg=(times[__LINE__].avg*99.0+t)/100.0; \
	if(t < times[__LINE__].min) times[__LINE__].min=t; \
	if(t > times[__LINE__].max) times[__LINE__].max=t; \
	if(PRINT_TIMES) printf("%85s: %4.1f   min,avg,max=%4.1f,%4.1f,%4.1f\n",#e,t,times[__LINE__].min, times[__LINE__].avg, times[__LINE__].max)



void rgb565_to_pseudo_hsv(unsigned short* in, unsigned char *color_out, unsigned char *gray_out)
{
	register int i;
	register unsigned short lut_value;
	for(i=0;i<320*240;i++)
	{
		lut_value = hsv_lut[ in[i] ];
		color_out[i] = (unsigned char)(lut_value & 0x00ff);
		gray_out[i]  = (unsigned char)(lut_value>>8);
	}
}

void ScanImageAndReduceC(Mat& I)
{
    // accept only char type matrices
    CV_Assert(I.depth() != sizeof(uchar));

    int channels = I.channels();

    int nRows = I.rows;
    int nCols = I.cols * channels;

    if (I.isContinuous())
    {
        nCols *= nRows;
        nRows = 1;
    }

    int i,j;
    uchar* p;
    for( i = 0; i < nRows; ++i)
    {
        p = I.ptr<uchar>(i);
        for ( j = 0; j < nCols; ++j)
        {
			//convert to BGR565
            p[j+0] = (p[j+0]>>3)<<3;  //5
            p[j+1] = (p[j+1]>>2)<<2;  //6
            p[j+2] = (p[j+2]>>3)<<3;  //5
			j+=2;
        }
    }
}



/** @function thresh_callback */
void contours(Mat& in, Mat& out, bool draw)
{
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	/// Find contours
	findContours( in, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

	/// Draw contours
	if(draw)
	{
		out.zeros( in.size(), CV_8UC3 );
		for( int i = 0; i< contours.size(); i++ )
		{
			Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
			drawContours( out, contours, i, color, 2, 8, hierarchy, 0, Point() );
		}
	}
}

int cv_setup(void)
{
	int i;

#ifdef WIN32
	capture.open("D:\\src\\opencv_test_dll\\Release\\file.h264");
#else
	capture.open(0);
	capture.set(CV_CAP_PROP_FRAME_WIDTH,320);
	capture.set(CV_CAP_PROP_FRAME_HEIGHT,240);

	printf("CV_CAP_PROP_FORMAT=%f\n",capture.get(CV_CAP_PROP_FORMAT));
	//capture.set(CV_CAP_PROP_FPS,30);
#endif

	capture.read(img[0]);

	cv_loop(); //run through it once to reach a more steady state

	for(i=0;i<1000;i++)  //now initialize the timing 
	{
		times[i].min=99999.0;
		times[i].avg=0.0;
		times[i].max=0.0;
	}

	for(i=0;i<320*240;i++)
	{
		rgb565_img[i] = rng.operator ushort();
	}

	return 0;
}



int cv_loop(void)
{
	printf("\n");

	skipped=0;  	while(skipped<skip)	{ capture.read(img[0]); skipped++;	} //skip if so desired

	T( capture.read(img[0]) ); //printf("img[0]: isContinuous()=%d channels()=%d  type()=%d  depth()=%d\n", img[0].isContinuous(), img[0].channels(), img[0].type(), img[0].depth()); //type=16

	T( cvtColor (img[0], img[1], COLOR_BGR2GRAY) );
	T( cvtColor (img[0], img[5], COLOR_BGR2HSV) );
	T( cvtColor (img[0], img[3], COLOR_BGR2BGR565) ); //printf("img[3]: channels()=%d  type()=%d  depth()=%d  size=%d  step=%d\n", img[3].channels(), img[3].type(), img[3].depth(), img[3].size, img[3].step1()  ); //type=8
	T( cvtColor (img[3], img[4], COLOR_BGR5652BGR) );

	T( resize(img[0], img[8], Size(), 0.5, 0.5, INTER_NEAREST) );
	T( resize(img[0], img[8], Size(), 0.5, 0.5, INTER_LINEAR ) );
	T( resize(img[0], img[8], Size(), 0.5, 0.5, INTER_AREA ) );
	T( resize(img[0], img[8], Size(), 0.5, 0.5, INTER_CUBIC ) );

	T( resize(img[1], img[9], Size(), 0.5, 0.5, INTER_NEAREST) );
	T( resize(img[1], img[9], Size(), 0.5, 0.5, INTER_LINEAR ) );
	T( resize(img[1], img[9], Size(), 0.5, 0.5, INTER_AREA ) );
	T( resize(img[1], img[7], Size(), 0.5, 0.5, INTER_CUBIC ) );
	T( resize(img[7], img[6], Size(), 2.0, 2.0, INTER_NEAREST) );

	T( medianBlur   (img[0], img[8], 3) );
	T( medianBlur   (img[0], img[8], 5) );
	T( GaussianBlur (img[0], img[8], Size(9, 9), 2, 2) );
	T( GaussianBlur (img[0], img[8], Size(5, 5), 2, 2) );
	T( GaussianBlur (img[0], img[8], Size(3, 3), 2, 2) );

	T( medianBlur   (img[1], img[9], 3) );
	T( medianBlur   (img[1], img[9], 5) );
	T( GaussianBlur (img[1], img[9], Size(9, 9), 2, 2) );
	T( GaussianBlur (img[1], img[9], Size(5, 5), 2, 2) );
	T( GaussianBlur (img[1], img[9], Size(3, 3), 2, 2) );
	T( blur         (img[1], img[9], Size(3,3)) );
	T( blur         (img[1], img[9], Size(5,5)) );

	T( Canny     (img[1], img[2], 50, 50, 3, 0) );
	T( Canny     (img[7], img[6], 50, 50, 3, 0) );
	T( Laplacian (img[1], img[9], 0) );

	vector<Vec3f> circles;
	T( HoughCircles (img[1], circles, CV_HOUGH_GRADIENT, 2, img[1].rows/4, 200, 100) );
    for( size_t i = 0; i < circles.size(); i++ )
    {
         Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
         int radius = cvRound(circles[i][2]);
         circle( img[0], center, 3, Scalar(0,255,0), -1, 8, 0 );
         circle( img[0], center, radius, Scalar(0,0,255), 3, 8, 0 );
    }

    vector<Vec2f> lines;
    T( HoughLines   ( img[2], lines, 1, CV_PI/200, 100 ) );
    for( size_t i = 0; i < lines.size(); i++ )
    {
        float rho = lines[i][0];
        float theta = lines[i][1];
        double a = cos(theta), b = sin(theta);
        double x0 = a*rho, y0 = b*rho;
        Point pt1(cvRound(x0 + 1000*(-b)),  cvRound(y0 + 1000*(a)));
        Point pt2(cvRound(x0 - 1000*(-b)),  cvRound(y0 - 1000*(a)));
        line( img[3], pt1, pt2, Scalar(0,0,255), 3, 8 );
    }


	T( inRange(img[5],Scalar(1,20,20),Scalar(128,255,255),img[9]) );


	T( img[0].copyTo(img[8]) );
	T( img[2].copyTo(img[9]) );
	T( contours(img[2], img[9], false) );

	T( ScanImageAndReduceC(img[0]) );

	//Mat dilateElement = getStructuringElement( MORPH_RECT,Size(5,5));
	//Mat erodeElement = getStructuringElement( MORPH_RECT,Size(3,3));
	T( dilate (img[2], img[9], getStructuringElement( MORPH_RECT,Size(3,3))) );
	T( dilate (img[2], img[9], getStructuringElement( MORPH_RECT,Size(5,5))) );
	T( erode  (img[2], img[9],  getStructuringElement( MORPH_RECT,Size(3,3))) );
	T( erode  (img[2], img[9],  getStructuringElement( MORPH_RECT,Size(5,5))) );

	T( threshold         (img[1], img[9], 100, 255, 0) );
	T( adaptiveThreshold (img[1], img[9], 128, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 3, 1) );

	T( bitwise_xor (img[1], img[2], img[9],	noArray()) );


	//resize(img[1],img[9],

	//cvtColor(img[4],img[3],COLOR_BGR2HSV);

	//printf("img[4]: channels()=%d  type()=%d  depth()=%d\n", img[4].channels(), img[4].type(), img[4].depth()); //type=0

	//compare 24-bit RGB with 16-bit RGB
	T( absdiff(img[4],img[0],img[8]) );  	
	T( absdiff(img[1],img[2],img[9]) );  	
	T( img[9] *= 32 ); //amplify the differences
	T( img[8] = img[1] * 32 ); //amplify the differences

	T( rgb565_to_pseudo_hsv(rgb565_img,out1,out2) );

	//Sobel
#if 0
	/// Generate grad_x and grad_y
	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y;
	/// Gradient X
	//Scharr( src_gray, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT );
	Sobel( img_gray, grad_x, CV_8U, 1, 0, 3, 1, 0, BORDER_DEFAULT );
	convertScaleAbs( grad_x, abs_grad_x );
	/// Gradient Y
	//Scharr( src_gray, grad_y, ddepth, 0, 1, scale, delta, BORDER_DEFAULT );
	Sobel( img_gray, grad_y, CV_8U, 0, 1, 3, 1, 0, BORDER_DEFAULT );
	convertScaleAbs( grad_y, abs_grad_y );
	/// Total Gradient (approximate)
	addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, img_temp );
#endif

	//cvtColor(img_temp,img_output,COLOR_GRAY2BGR);

	//imshow("test",img_input);
	//waitKey(1);
	return 0;
}




#ifndef WIN32

int main(void)
{
	cv_setup();
	while(1)
	{
		cv_loop();
		//imshow("img[0]",img[0]);
		//waitKey(100);
	}
	return 0;
}

#endif
