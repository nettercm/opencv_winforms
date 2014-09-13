
#include <sstream>
#include <string>
#include <iostream>
#include <stdio.h>

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <Windows.h>
/*
ilmimf.lib;zlib.lib;libjasper.lib;libpng.lib;libtiff.lib;libjpeg.lib;opencv_photo249.lib;opencv_features2d249.lib;opencv_gpu249.lib;opencv_objdetect249.lib;opencv_video249.lib;opencv_videostab249.lib;opencv_legacy249.lib;opencv_flann249.lib;opencv_contrib249.lib;opencv_core249.lib;opencv_highgui249.lib;opencv_imgproc249.lib;Comctl32.lib;Vfw32.lib;
*/

using namespace std;
using namespace cv;

//default capture width and height
int FRAME_WIDTH = 320; //640;
int FRAME_HEIGHT = 240; //480;
//max number of objects to be detected in frame
int MAX_NUM_OBJECTS=50;
//minimum and maximum object area
int MIN_OBJECT_AREA = 20*20;
int MAX_OBJECT_AREA = FRAME_HEIGHT*FRAME_WIDTH/1.5;

uchar h_min=255,h_max=0,s_min=255,s_max=0,v_min=255,v_max=0;
double canny_t1=50, canny_t2=50;

VideoCapture capture;
Mat img[40];
char *img_name[40];
Mat img_temp;
Mat img_stream;
volatile int stream_frames=0;
Mat img_previous1,img_previous2;
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
		for( int i = 0; (i< contours.size()); i++ )
		{
			Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
			drawContours( out, contours, i, color, 1, 8, hierarchy, 0, Point() );
		}
	}
}


string intToString(int number)
{
	std::stringstream ss;
	ss << number;
	return ss.str();
}


void drawObject(int x, int y,Mat &frame)
{
	//use some of the openCV drawing functions to draw crosshairs
	//on your tracked image!

	//UPDATE:JUNE 18TH, 2013
	//added 'if' and 'else' statements to prevent
	//memory errors from writing off the screen (ie. (-25,-25) is not within the window!)

	circle(frame,Point(x,y),20,Scalar(0,255,0),2);
	if(y-25>0)
		line(frame,Point(x,y),Point(x,y-25),Scalar(0,255,0),2);
	else line(frame,Point(x,y),Point(x,0),Scalar(0,255,0),2);
	if(y+25<320)
		line(frame,Point(x,y),Point(x,y+25),Scalar(0,255,0),2);
	else line(frame,Point(x,y),Point(x,320),Scalar(0,255,0),2);
	if(x-25>0)
		line(frame,Point(x,y),Point(x-25,y),Scalar(0,255,0),2);
	else line(frame,Point(x,y),Point(0,y),Scalar(0,255,0),2);
	if(x+25<320)
		line(frame,Point(x,y),Point(x+25,y),Scalar(0,255,0),2);
	else line(frame,Point(x,y),Point(320,y),Scalar(0,255,0),2);

	putText(frame,intToString(x)+","+intToString(y),Point(x,y+30),1,1,Scalar(0,255,0),2);

}

void trackFilteredObject(int &x, int &y, Mat threshold_image, Mat &cameraFeed)
{
	Mat temp;
	threshold_image.copyTo(temp);
	//these two vectors needed for output of findContours
	vector< vector<Point> > contours;
	vector<Vec4i> hierarchy;
	//find contours of filtered image using openCV findContours function
	findContours(temp,contours,hierarchy,CV_RETR_CCOMP,CV_CHAIN_APPROX_SIMPLE );
	//use moments method to find our filtered object
	double refArea = 0;
	bool objectFound = false;
	if (hierarchy.size() > 0) {
		int numObjects = hierarchy.size();
		//if number of objects greater than MAX_NUM_OBJECTS we have a noisy filter
		if(numObjects<MAX_NUM_OBJECTS){
			for (int index = 0; index >= 0; index = hierarchy[index][0]) {

				Moments moment = moments((cv::Mat)contours[index]);
				double area = moment.m00;

				//if the area is less than 20 px by 20px then it is probably just noise
				//if the area is the same as the 3/2 of the image size, probably just a bad filter
				//we only want the object with the largest area so we safe a reference area each
				//iteration and compare it to the area in the next iteration.
				if(area>MIN_OBJECT_AREA && area<MAX_OBJECT_AREA && area>refArea){
					x = moment.m10/area;
					y = moment.m01/area;
					objectFound = true;
					refArea = area;
				}else objectFound = false;


			}
			//let user know you found an object
			if(objectFound ==true){
				putText(cameraFeed,"Tracking Object",Point(0,50),2,1,Scalar(0,255,0),2);
				//draw object location on screen
				drawObject(x,y,cameraFeed);}

		}else putText(cameraFeed,"TOO MUCH NOISE! ADJUST FILTER",Point(0,50),1,2,Scalar(0,0,255),2);
	}
}



int cv_capture(void)
{
	if(skip<0)
	{
		img_previous1.copyTo(img[0]);
	}
	else
	{
		skipped=0;  	while(skipped<skip)	{ capture.read(img[0]); skipped++;	} //skip if so desired
		T( capture.read(img[0]) ); //printf("img[0]: isContinuous()=%d channels()=%d  type()=%d  depth()=%d\n", img[0].isContinuous(), img[0].channels(), img[0].type(), img[0].depth()); //type=16
		img_previous1.copyTo(img_previous2);
		img[0].copyTo(img_previous1);
	}
	resize(img[0], img[0], Size(FRAME_WIDTH,FRAME_HEIGHT), 0.0, 0.0, INTER_AREA );
	if(img[0].cols != img_previous2.cols) img[0].copyTo(img_previous2);
	if(img[0].cols != img_previous1.cols) img[0].copyTo(img_previous1);

	return 0;
}


int cv_capture_from_stream(void)
{
	static int last_stream_frames=0;
	if(skip<0)
	{
		img_previous1.copyTo(img[0]);
	}
	else
	{
		skipped=0;  	
		while(skipped<skip)	
		{ 
			while(last_stream_frames==stream_frames) Sleep(5);
			skipped++;	
			last_stream_frames=stream_frames;
		} //skip if so desired
		while(last_stream_frames==stream_frames) Sleep(2);
		last_stream_frames=stream_frames;
		img_stream.copyTo(img[0]);
		img_previous1.copyTo(img_previous2);
		img[0].copyTo(img_previous1);
	}
	resize(img[0], img[0], Size(FRAME_WIDTH,FRAME_HEIGHT), 0.0, 0.0, INTER_AREA );
	if(img[0].cols != img_previous2.cols) img[0].copyTo(img_previous2);
	if(img[0].cols != img_previous1.cols) img[0].copyTo(img_previous1);

	return 0;
}



int cv_loop(void)
{
	T( cvtColor (img[0], img[1], COLOR_BGR2GRAY) );

	T( cvtColor (img[0], img[2], COLOR_BGR2HSV) );
	T( cvtColor (img[0], img[3], COLOR_BGR2BGR565) ); //printf("img[3]: channels()=%d  type()=%d  depth()=%d  size=%d  step=%d\n", img[3].channels(), img[3].type(), img[3].depth(), img[3].size, img[3].step1()  ); //type=8
	T( cvtColor (img[3], img[4], COLOR_BGR5652BGR) );

	T( resize(img[0], img[39], Size(), 0.5, 0.5, INTER_NEAREST) );
	T( resize(img[0], img[39], Size(), 0.5, 0.5, INTER_LINEAR ) );
	T( resize(img[0], img[39], Size(), 0.5, 0.5, INTER_AREA ) );
	T( resize(img[0], img[39], Size(), 0.5, 0.5, INTER_CUBIC ) );

	T( resize(img[1], img[39], Size(), 0.5, 0.5, INTER_NEAREST) );
	T( resize(img[1], img[39], Size(), 0.5, 0.5, INTER_LINEAR ) );
	T( resize(img[1], img[39], Size(), 0.5, 0.5, INTER_AREA ) );

	T( resize(img[1], img[5], Size(), 0.5, 0.5, INTER_AREA ) );
	T( resize(img[5], img[6], Size(), 2.0, 2.0, INTER_NEAREST) );

	T( medianBlur   (img[0], img[7], 3) );
	T( medianBlur   (img[0], img[8], 5) );
	T( GaussianBlur (img[0], img[9], Size(9, 9), 2, 2) );
	T( GaussianBlur (img[0], img[10], Size(5, 5), 2, 2) );
	T( GaussianBlur (img[0], img[11], Size(3, 3), 2, 2) );

	T( medianBlur   (img[1], img[12], 3) );
	T( medianBlur   (img[1], img[13], 5) );
	T( GaussianBlur (img[1], img[14], Size(9, 9), 2, 2) );
	T( GaussianBlur (img[1], img[15], Size(5, 5), 2, 2) );
	T( GaussianBlur (img[1], img[16], Size(3, 3), 2, 2) );
	T( blur         (img[1], img[17], Size(3,3)) );
	T( blur         (img[1], img[18], Size(5,5)) );

	T( Canny     (img[1], img[19], canny_t1, canny_t2, 3, 0) );
	T( Canny     (img[5], img[20], canny_t1, canny_t2, 3, 0) );
	T( Laplacian (img[1], img[21], 0) );

#if 0
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
#endif

	T( inRange(img[2],Scalar(h_min,s_min,v_min),Scalar(h_max,s_max,v_max),img[22]) );


	T( img[0].copyTo(img[39]) );
	T( img[2].copyTo(img[39]) );

	T( ScanImageAndReduceC(img[39]) );

	T( erode  (img[22], img[25],  getStructuringElement( MORPH_RECT,Size(3,3))) );
	T( erode  (img[22], img[26],  getStructuringElement( MORPH_RECT,Size(5,5))) );
	T( dilate (img[25], img[23], getStructuringElement( MORPH_RECT,Size(3,3))) );
	T( dilate (img[26], img[24], getStructuringElement( MORPH_RECT,Size(5,5))) );

	T( threshold         (img[1], img[27], 100, 255, 0) );
	T( adaptiveThreshold (img[1], img[28], 128, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 3, 1) );

	T( bitwise_xor (img[1], img[19], img[29],	noArray()) );

	//printf("img[4]: channels()=%d  type()=%d  depth()=%d\n", img[4].channels(), img[4].type(), img[4].depth()); //type=0

	//compare 24-bit RGB with 16-bit RGB
	T( absdiff(img[4],img[0],img[30]) );  	
	T( absdiff(img[1],img[6],img[31]) );  	
	//T( img[30] *= 32 ); //amplify the differences
	T( img[31] *= 16 ); //amplify the differences
	T( img[30].convertTo(img[32],-1,16,0) );

	//frame-differencing
	absdiff(img[0],img_previous2,img[33]);
	cvtColor (img_previous2,img[39], COLOR_BGR2GRAY);
	absdiff(img[1],img[39],img[34]);


	/*
	Mat lookUpTable(1, 256, CV_8U);
	uchar* p = lookUpTable.data;
	for( int i = 0; i < 256; ++i) p[i] = (i*32 > 255 ? 255 : i*32);
	LUT(img[30], lookUpTable, img[32]);
	*/

	T( rgb565_to_pseudo_hsv(rgb565_img,out1,out2) );

	T( img[1].copyTo(img[39]) );
	T( contours(img[39], img[33], false) );

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

	return 0;
}




int cv_setup(void)
{
	int i;

#ifdef WIN32
	capture.open("D:\\src\\win32_opencv_test_dll\\Release\\file.h264");
	//capture.open("C:\\cygwin\\home\\Chris\\7.h264");
#else
	capture.open(0);
	capture.set(CV_CAP_PROP_FRAME_WIDTH,320);
	capture.set(CV_CAP_PROP_FRAME_HEIGHT,240);

	printf("CV_CAP_PROP_FORMAT=%f\n",capture.get(CV_CAP_PROP_FORMAT));
	//capture.set(CV_CAP_PROP_FPS,30);
#endif

	capture.read(img[0]);
	img[0].copyTo(img_previous1);
	img[0].copyTo(img_previous2);

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
