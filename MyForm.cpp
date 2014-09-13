#include "MyForm.h"
#include "settings_dialog.h"
// robot_ui.cpp : main project file.

#include <stdio.h>
#include <windows.h>
#include <Winuser.h>

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "hid.lib")
#pragma comment(lib, "winmm.lib")

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


extern "C" 
{
	void show_image(int h, int w, unsigned char *data);
	int avio_reading_main(int argc, char *argv[]);
}


using namespace std;
using namespace cv;
using namespace opencv_winforms;

Mat img_from_camera;

extern int cv_setup(void);
extern int cv_loop(void);
extern int cv_capture(void);
extern Mat img[40];
extern Mat img_temp;
extern int skip,skipped;
extern uchar h_min,h_max,s_min,s_max,v_min,v_max;
extern double canny_t1,canny_t2;
extern int FRAME_WIDTH,FRAME_HEIGHT;

void show_image(int h, int w, unsigned char *data)
{
	/*
	cv::Mat canny;
	cv::Mat img(h,w,CV_8UC3,data);
	//cv::Mat img(pFrame->height,pFrame->width,CV_8UC3,pFrameRGB->data[0]); //dst->data[0]);
	cv::GaussianBlur(img,img,cv::Size(3,3),0);
	cv::Canny(img,canny,100,100);
    cv::imshow("display",img);
    cv::imshow("canny",canny);
    cvWaitKey(1);
	*/
	cv::Mat tmp(h,w,CV_8UC3,data);
	tmp.copyTo(img[0]);

}





[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	AllocConsole();
	freopen("CON","wb",stdout);
	//FreeConsole();

	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Create the main window and run it
	Application::Run(gcnew MyForm());
	return 0;
}


void populate_image_combo_boxes(System::Windows::Forms::ComboBox^ cb, int select)
{
	cb->Items->Clear();
	cb->Items->AddRange(gcnew cli::array< System::Object^  >(35) 
	{
		L" 0 - Original input image in 24-bit RGB", 
		L" 1 - Original input image in 8-bit Gray", 
		L" 2 - Original input image in HSV",
		L" 3 - Original input image in 16-bit RGB565",
		L" 4 - Original input -> RGB565 -> RGB888",
		L" 5 - Low-res (0.5,0.5) 8-bit grayscale",
		L" 6 - Original gray -> downsample -> upsample",
		L" 7 - Original RGB -> medianBlur(3,3)",
		L" 8 - Original RGB -> medianBlur(5,5)",
		L" 9 - Original RGB -> GaussianBlur(9,9)",
		L"10 - Original RGB -> GaussianBlur(5,5)",
		L"11 - Original RGB -> GaussianBlur(3,3)",
		L"12 - ",
		L"13 - ",
		L"14 - ",
		L"15 - ",
		L"16 - ",
		L"17 - ",
		L"18 - ",
		L"19 - high-res gray -> Canny(3)",
		L"20 - low-res gray -> Canny(3)",
		L"21 - high-res gray -> Laplacian()",
		L"22 - HSV image -> inRange(), i.e. color blob",
		L"23 - Gray -> Canny() -> dilate(3,3)",
		L"24 - Gray -> Canny() -> dilate(5,5)",
		L"25 - Gray -> Canny() -> erode(3,3)",
		L"26 - Gray -> Canny() -> erode(5,5)",
		L"27 - ",
		L"28 - ",
		L"29 - ",
		L"30 - ",
		L"31 - Difference between high-res and low-res grayscle",
		L"32 - Difference between 24-bit RGB and 16-bit RGB",
		L"33 - Motion (RGB)",
		L"34 - Motion (Gray)"
	});
	cb->SelectedIndex=select;
}

MyForm::MyForm(void)
{
	printf("MyForm()\n");
	InitializeComponent();
	timeBeginPeriod(1);
	cv_setup();
	populate_image_combo_boxes(comboBox_img1,0);
	populate_image_combo_boxes(comboBox_img2,1);
	populate_image_combo_boxes(comboBox_img3,2);
	populate_image_combo_boxes(comboBox_img4,33);
	populate_image_combo_boxes(comboBox_img5,19);
	populate_image_combo_boxes(comboBox_img6,22);
}



System::Void MyForm::MyForm_Load(System::Object^  sender, System::EventArgs^  e) 
{
	printf("MyForm_Load()\n");
	backgroundWorker1->RunWorkerAsync();
}



void MyForm::show_image(Mat image, System::Windows::Forms::PictureBox^ pictureBox)
{
	Mat temp;
	if(image.type()==0) cv::cvtColor(image,temp,COLOR_GRAY2BGR); //from gray
	else if(image.type()==8) cv::cvtColor(image,temp,COLOR_BGR5652BGR); //from bgr565
	else image.copyTo(temp); //presumably already in bgr - nothing to do...
	cv::resize(temp, temp, cv::Size(320,240), 0.0, 0.0, INTER_NEAREST );
	System::Drawing::Graphics^ graphics = pictureBox->CreateGraphics();
	System::IntPtr ptr(temp.ptr());
	System::Drawing::Bitmap^ b  = gcnew System::Drawing::Bitmap(temp.cols,temp.rows,temp.step,System::Drawing::Imaging::PixelFormat::Format24bppRgb,ptr);
	System::Drawing::RectangleF rect(0,0,pictureBox->Width,pictureBox1->Height);
	graphics->DrawImage(b,rect);	
}



System::Void MyForm::timer1_Tick(System::Object^  sender, System::EventArgs^  e) 
{
	if(checkBox1->Checked)
	{
		fps++;
		switch(comboBox_imgsize->SelectedIndex)
		{
		case 0:
			FRAME_WIDTH=320; FRAME_HEIGHT=240;
			break;
		case 1:
			FRAME_WIDTH=160; FRAME_HEIGHT=120;
			break;
		case 2:
			FRAME_WIDTH=80; FRAME_HEIGHT=60;
			break;
		case 3:
			FRAME_WIDTH=40; FRAME_HEIGHT=30;
			break;
		}
		if(checkBox_Pause->Checked) skip = -1; else skip = System::Convert::ToInt32(comboBox2->Text);
		cv_capture();
		cv_loop();
		show_image(img[comboBox_img1->SelectedIndex],pictureBox1);
		show_image(img[comboBox_img2->SelectedIndex],pictureBox2);
		show_image(img[comboBox_img3->SelectedIndex],pictureBox3);
		show_image(img[comboBox_img4->SelectedIndex],pictureBox4);
		show_image(img[comboBox_img5->SelectedIndex],pictureBox5);
		show_image(img[comboBox_img6->SelectedIndex],pictureBox6);
		//show_image(img_from_camera,pictureBox1);
		GC::Collect();
	}
}



System::Void MyForm::timer2_Tick(System::Object^  sender, System::EventArgs^  e) 
{
	lbl_fps->Text=fps.ToString() + " fps";
	fps=0;
}



System::Void MyForm::pictureBox1_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
{
	float x,y;
	int X,Y;
	float x_scale, y_scale;
	PictureBox ^pb = safe_cast<PictureBox^>(sender); 
	MouseEventArgs ^me = safe_cast<MouseEventArgs^>(e);

	x_scale = img[2].cols;
	y_scale = img[2].rows;

	x=me->X; if(x<0) x=0;
	y=me->Y; if(y<0) y=0;
	x=x_scale*(x/(float)pb->Size.Width);
	y=y_scale*(y/(float)pb->Size.Height);
	if(x>x_scale) x=x_scale;
	if(y>y_scale) y=y_scale;
	X=x;
	Y=y;

	Vec3b hsv = img[2].at<Vec3b>(Y, X);
	uchar h = hsv.val[0];
	uchar s = hsv.val[1];
	uchar v = hsv.val[2];
	txt_H->Text=h.ToString();
	txt_S->Text=s.ToString();
	txt_V->Text=v.ToString();

	x_scale = img[0].cols;
	y_scale = img[0].rows;

	x=me->X; if(x<0) x=0;
	y=me->Y; if(y<0) y=0;
	x=x_scale*(x/(float)pb->Size.Width);
	y=y_scale*(y/(float)pb->Size.Height);
	if(x>x_scale) x=x_scale;
	if(y>y_scale) y=y_scale;
	X=x;
	Y=y;

	Vec3b rgb = img[0].at<Vec3b>(Y, X);
	uchar b = rgb.val[0];
	uchar g = rgb.val[1];
	uchar r = rgb.val[2];
	txt_R->Text=r.ToString();
	txt_G->Text=g.ToString();
	txt_B->Text=b.ToString();


	if(me->Button != System::Windows::Forms::MouseButtons::None)
	{
		fps=fps;
		printf("x,y=%f,%f   e.x,e.y=%d,%d   w,h=%d,%d\n",x,y, me->X, me->Y, pictureBox1->Size.Width, pictureBox1->Size.Height);
		if(h<h_min) h_min=h;
		if(h>h_max) h_max=h;
		if(s<s_min) s_min=s;
		if(s>s_max) s_max=s;
		if(v<v_min) v_min=v;
		if(v>v_max) v_max=v;
	}
}



System::Void MyForm::pictureBox1_Click(System::Object^  sender, System::EventArgs^  e) 
{
	MouseEventArgs ^me = safe_cast<MouseEventArgs^>(e);
	pictureBox1_MouseMove(sender, me);
}



System::Void MyForm::comboBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) 
{
	timer1->Interval = System::Convert::ToInt32(comboBox1->Text);
}



System::Void MyForm::pictureBox1_DoubleClick(System::Object^  sender, System::EventArgs^  e) 
{
}



System::Void MyForm::button1_Click(System::Object^  sender, System::EventArgs^  e) 
{
	settings = (gcnew settings_dialog());
	settings->Show();
}



System::Void MyForm::backgroundWorker1_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e)
{
	printf("++backgroundWorker1_DoWork()\n");
	//avio_reading_main(0,NULL);
	printf("--backgroundWorker1_DoWork()\n");
}

