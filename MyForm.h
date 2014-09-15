#pragma once

#include <sstream>
#include <string>
#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <Winuser.h>

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "settings_dialog.h"

using namespace std;
using namespace cv;

extern int cv_setup(void);
extern int cv_loop(void);
extern int cv_capture(void);
extern Mat img[40];
extern Mat img_temp;
extern int skip,skipped;
extern unsigned char h_min,h_max,s_min,s_max,v_min,v_max;
extern double canny_t1,canny_t2;
extern int FRAME_WIDTH,FRAME_HEIGHT;

namespace opencv_winforms {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public: MyForm(void);
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
		//	private: void show_image(Mat image, System::Windows::Forms::PictureBox^ pictureBox);
	private: settings_dialog^ settings;
	private: int fps;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel1;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::CheckBox^  checkBox1;
	private: System::Windows::Forms::Label^  lbl_fps;
	private: System::Windows::Forms::Timer^  timer2;
	private: System::Windows::Forms::PictureBox^  pictureBox2;
	private: System::Windows::Forms::PictureBox^  pictureBox3;
	private: System::Windows::Forms::PictureBox^  pictureBox4;
	private: System::Windows::Forms::ComboBox^  comboBox1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::ComboBox^  comboBox2;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::PictureBox^  pictureBox5;
	private: System::Windows::Forms::PictureBox^  pictureBox6;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Label^  label3;


	private: System::Windows::Forms::TextBox^  txt_H;
	private: System::Windows::Forms::TextBox^  txt_S;
	private: System::Windows::Forms::TextBox^  txt_V;
	private: System::ComponentModel::BackgroundWorker^  backgroundWorker1;
	private: System::Windows::Forms::ComboBox^  comboBox_img1;
	private: System::Windows::Forms::ComboBox^  comboBox_img2;


	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::TextBox^  txt_R;
	private: System::Windows::Forms::TextBox^  txt_G;
	private: System::Windows::Forms::TextBox^  txt_B;



	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::TextBox^  txt_Y;
	private: System::Windows::Forms::TextBox^  txt_Cb;
	private: System::Windows::Forms::TextBox^  txt_Cr;
	private: System::Windows::Forms::CheckBox^  checkBox_Pause;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::ComboBox^  comboBox_imgsize;
	private: System::Windows::Forms::ComboBox^  comboBox_img3;
	private: System::Windows::Forms::ComboBox^  comboBox_img4;
	private: System::Windows::Forms::ComboBox^  comboBox_img5;
	private: System::Windows::Forms::ComboBox^  comboBox_img6;
	private: System::Windows::Forms::CheckBox^  checkBox_process;





















	protected: 
	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox4 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox5 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox6 = (gcnew System::Windows::Forms::PictureBox());
			this->comboBox_img1 = (gcnew System::Windows::Forms::ComboBox());
			this->comboBox_img2 = (gcnew System::Windows::Forms::ComboBox());
			this->comboBox_img3 = (gcnew System::Windows::Forms::ComboBox());
			this->comboBox_img4 = (gcnew System::Windows::Forms::ComboBox());
			this->comboBox_img5 = (gcnew System::Windows::Forms::ComboBox());
			this->comboBox_img6 = (gcnew System::Windows::Forms::ComboBox());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->lbl_fps = (gcnew System::Windows::Forms::Label());
			this->timer2 = (gcnew System::Windows::Forms::Timer(this->components));
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->comboBox2 = (gcnew System::Windows::Forms::ComboBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->txt_H = (gcnew System::Windows::Forms::TextBox());
			this->txt_S = (gcnew System::Windows::Forms::TextBox());
			this->txt_V = (gcnew System::Windows::Forms::TextBox());
			this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->txt_R = (gcnew System::Windows::Forms::TextBox());
			this->txt_G = (gcnew System::Windows::Forms::TextBox());
			this->txt_B = (gcnew System::Windows::Forms::TextBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->txt_Y = (gcnew System::Windows::Forms::TextBox());
			this->txt_Cb = (gcnew System::Windows::Forms::TextBox());
			this->txt_Cr = (gcnew System::Windows::Forms::TextBox());
			this->checkBox_Pause = (gcnew System::Windows::Forms::CheckBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->comboBox_imgsize = (gcnew System::Windows::Forms::ComboBox());
			this->checkBox_process = (gcnew System::Windows::Forms::CheckBox());
			this->tableLayoutPanel1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox4))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox5))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox6))->BeginInit();
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Interval = 33;
			this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->tableLayoutPanel1->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->tableLayoutPanel1->CellBorderStyle = System::Windows::Forms::TableLayoutPanelCellBorderStyle::Single;
			this->tableLayoutPanel1->ColumnCount = 3;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				33.33333F)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				33.33333F)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				33.33333F)));
			this->tableLayoutPanel1->Controls->Add(this->pictureBox1, 0, 1);
			this->tableLayoutPanel1->Controls->Add(this->pictureBox2, 1, 1);
			this->tableLayoutPanel1->Controls->Add(this->pictureBox3, 2, 1);
			this->tableLayoutPanel1->Controls->Add(this->pictureBox4, 0, 3);
			this->tableLayoutPanel1->Controls->Add(this->pictureBox5, 1, 3);
			this->tableLayoutPanel1->Controls->Add(this->pictureBox6, 2, 3);
			this->tableLayoutPanel1->Controls->Add(this->comboBox_img1, 0, 0);
			this->tableLayoutPanel1->Controls->Add(this->comboBox_img2, 1, 0);
			this->tableLayoutPanel1->Controls->Add(this->comboBox_img3, 2, 0);
			this->tableLayoutPanel1->Controls->Add(this->comboBox_img4, 0, 2);
			this->tableLayoutPanel1->Controls->Add(this->comboBox_img5, 1, 2);
			this->tableLayoutPanel1->Controls->Add(this->comboBox_img6, 2, 2);
			this->tableLayoutPanel1->Location = System::Drawing::Point(2, 67);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 4;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 26)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 26)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(982, 551);
			this->tableLayoutPanel1->TabIndex = 0;
			// 
			// pictureBox1
			// 
			this->pictureBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->pictureBox1->Location = System::Drawing::Point(4, 31);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(320, 241);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Click += gcnew System::EventHandler(this, &MyForm::pictureBox1_Click);
			this->pictureBox1->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox1_MouseMove);
			// 
			// pictureBox2
			// 
			this->pictureBox2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->pictureBox2->Location = System::Drawing::Point(331, 31);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(320, 241);
			this->pictureBox2->TabIndex = 1;
			this->pictureBox2->TabStop = false;
			this->pictureBox2->Click += gcnew System::EventHandler(this, &MyForm::pictureBox1_Click);
			this->pictureBox2->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox1_MouseMove);
			// 
			// pictureBox3
			// 
			this->pictureBox3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->pictureBox3->Location = System::Drawing::Point(658, 31);
			this->pictureBox3->Name = L"pictureBox3";
			this->pictureBox3->Size = System::Drawing::Size(320, 241);
			this->pictureBox3->TabIndex = 2;
			this->pictureBox3->TabStop = false;
			this->pictureBox3->Click += gcnew System::EventHandler(this, &MyForm::pictureBox1_Click);
			this->pictureBox3->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox1_MouseMove);
			// 
			// pictureBox4
			// 
			this->pictureBox4->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->pictureBox4->Location = System::Drawing::Point(4, 306);
			this->pictureBox4->Name = L"pictureBox4";
			this->pictureBox4->Size = System::Drawing::Size(320, 241);
			this->pictureBox4->TabIndex = 3;
			this->pictureBox4->TabStop = false;
			this->pictureBox4->Click += gcnew System::EventHandler(this, &MyForm::pictureBox1_Click);
			this->pictureBox4->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox1_MouseMove);
			// 
			// pictureBox5
			// 
			this->pictureBox5->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->pictureBox5->Location = System::Drawing::Point(331, 306);
			this->pictureBox5->Name = L"pictureBox5";
			this->pictureBox5->Size = System::Drawing::Size(320, 241);
			this->pictureBox5->TabIndex = 4;
			this->pictureBox5->TabStop = false;
			this->pictureBox5->Click += gcnew System::EventHandler(this, &MyForm::pictureBox1_Click);
			this->pictureBox5->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox1_MouseMove);
			// 
			// pictureBox6
			// 
			this->pictureBox6->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->pictureBox6->Location = System::Drawing::Point(658, 306);
			this->pictureBox6->Name = L"pictureBox6";
			this->pictureBox6->Size = System::Drawing::Size(320, 241);
			this->pictureBox6->TabIndex = 5;
			this->pictureBox6->TabStop = false;
			this->pictureBox6->Click += gcnew System::EventHandler(this, &MyForm::pictureBox1_Click);
			this->pictureBox6->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox1_MouseMove);
			// 
			// comboBox_img1
			// 
			this->comboBox_img1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->comboBox_img1->BackColor = System::Drawing::SystemColors::Window;
			this->comboBox_img1->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox_img1->FormattingEnabled = true;
			this->comboBox_img1->Items->AddRange(gcnew cli::array< System::Object^  >(3) {L"a", L"b", L"c"});
			this->comboBox_img1->Location = System::Drawing::Point(4, 4);
			this->comboBox_img1->Name = L"comboBox_img1";
			this->comboBox_img1->Size = System::Drawing::Size(320, 21);
			this->comboBox_img1->TabIndex = 6;
			// 
			// comboBox_img2
			// 
			this->comboBox_img2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->comboBox_img2->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox_img2->FormattingEnabled = true;
			this->comboBox_img2->Location = System::Drawing::Point(331, 4);
			this->comboBox_img2->Name = L"comboBox_img2";
			this->comboBox_img2->Size = System::Drawing::Size(320, 21);
			this->comboBox_img2->TabIndex = 7;
			// 
			// comboBox_img3
			// 
			this->comboBox_img3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->comboBox_img3->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox_img3->FormattingEnabled = true;
			this->comboBox_img3->Location = System::Drawing::Point(658, 4);
			this->comboBox_img3->Name = L"comboBox_img3";
			this->comboBox_img3->Size = System::Drawing::Size(320, 21);
			this->comboBox_img3->TabIndex = 7;
			// 
			// comboBox_img4
			// 
			this->comboBox_img4->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->comboBox_img4->BackColor = System::Drawing::SystemColors::Window;
			this->comboBox_img4->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox_img4->FormattingEnabled = true;
			this->comboBox_img4->Items->AddRange(gcnew cli::array< System::Object^  >(3) {L"a", L"b", L"c"});
			this->comboBox_img4->Location = System::Drawing::Point(4, 279);
			this->comboBox_img4->Name = L"comboBox_img4";
			this->comboBox_img4->Size = System::Drawing::Size(320, 21);
			this->comboBox_img4->TabIndex = 6;
			// 
			// comboBox_img5
			// 
			this->comboBox_img5->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->comboBox_img5->BackColor = System::Drawing::SystemColors::Window;
			this->comboBox_img5->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox_img5->FormattingEnabled = true;
			this->comboBox_img5->Items->AddRange(gcnew cli::array< System::Object^  >(3) {L"a", L"b", L"c"});
			this->comboBox_img5->Location = System::Drawing::Point(331, 279);
			this->comboBox_img5->Name = L"comboBox_img5";
			this->comboBox_img5->Size = System::Drawing::Size(320, 21);
			this->comboBox_img5->TabIndex = 6;
			// 
			// comboBox_img6
			// 
			this->comboBox_img6->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->comboBox_img6->BackColor = System::Drawing::SystemColors::Window;
			this->comboBox_img6->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox_img6->FormattingEnabled = true;
			this->comboBox_img6->Items->AddRange(gcnew cli::array< System::Object^  >(3) {L"a", L"b", L"c"});
			this->comboBox_img6->Location = System::Drawing::Point(658, 279);
			this->comboBox_img6->Name = L"comboBox_img6";
			this->comboBox_img6->Size = System::Drawing::Size(320, 21);
			this->comboBox_img6->TabIndex = 6;
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Location = System::Drawing::Point(6, 4);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(88, 17);
			this->checkBox1->TabIndex = 1;
			this->checkBox1->Text = L"Enable video";
			this->checkBox1->UseVisualStyleBackColor = true;
			// 
			// lbl_fps
			// 
			this->lbl_fps->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->lbl_fps->AutoSize = true;
			this->lbl_fps->Location = System::Drawing::Point(947, 16);
			this->lbl_fps->Name = L"lbl_fps";
			this->lbl_fps->Size = System::Drawing::Size(36, 13);
			this->lbl_fps->TabIndex = 2;
			this->lbl_fps->Text = L"30 fps";
			// 
			// timer2
			// 
			this->timer2->Enabled = true;
			this->timer2->Interval = 1000;
			this->timer2->Tick += gcnew System::EventHandler(this, &MyForm::timer2_Tick);
			// 
			// comboBox1
			// 
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Items->AddRange(gcnew cli::array< System::Object^  >(10) {L"1", L"5", L"10", L"25", L"33", L"50", L"100", 
				L"200", L"500", L"1000"});
			this->comboBox1->Location = System::Drawing::Point(186, 8);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(49, 21);
			this->comboBox1->TabIndex = 3;
			this->comboBox1->Text = L"33";
			this->comboBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::comboBox1_SelectedIndexChanged);
			this->comboBox1->TextChanged += gcnew System::EventHandler(this, &MyForm::comboBox1_SelectedIndexChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(114, 11);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(67, 13);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Interval (ms):";
			// 
			// comboBox2
			// 
			this->comboBox2->FormattingEnabled = true;
			this->comboBox2->Items->AddRange(gcnew cli::array< System::Object^  >(11) {L"0", L"1", L"2", L"3", L"4", L"5", L"6", L"7", 
				L"8", L"9", L"10"});
			this->comboBox2->Location = System::Drawing::Point(294, 8);
			this->comboBox2->Name = L"comboBox2";
			this->comboBox2->Size = System::Drawing::Size(42, 21);
			this->comboBox2->TabIndex = 3;
			this->comboBox2->Text = L"0";
			this->comboBox2->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::comboBox1_SelectedIndexChanged);
			this->comboBox2->TextChanged += gcnew System::EventHandler(this, &MyForm::comboBox1_SelectedIndexChanged);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(257, 11);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(31, 13);
			this->label2->TabIndex = 2;
			this->label2->Text = L"Skip:";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(516, 6);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 4;
			this->button1->Text = L"Settings";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(621, 4);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(32, 13);
			this->label3->TabIndex = 5;
			this->label3->Text = L"HSV:";
			// 
			// txt_H
			// 
			this->txt_H->Location = System::Drawing::Point(660, 1);
			this->txt_H->Name = L"txt_H";
			this->txt_H->Size = System::Drawing::Size(43, 20);
			this->txt_H->TabIndex = 6;
			// 
			// txt_S
			// 
			this->txt_S->Location = System::Drawing::Point(706, 1);
			this->txt_S->Name = L"txt_S";
			this->txt_S->Size = System::Drawing::Size(43, 20);
			this->txt_S->TabIndex = 6;
			// 
			// txt_V
			// 
			this->txt_V->Location = System::Drawing::Point(753, 1);
			this->txt_V->Name = L"txt_V";
			this->txt_V->Size = System::Drawing::Size(43, 20);
			this->txt_V->TabIndex = 6;
			// 
			// backgroundWorker1
			// 
			this->backgroundWorker1->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &MyForm::backgroundWorker1_DoWork);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(621, 25);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(33, 13);
			this->label4->TabIndex = 5;
			this->label4->Text = L"RGB:";
			// 
			// txt_R
			// 
			this->txt_R->Location = System::Drawing::Point(660, 22);
			this->txt_R->Name = L"txt_R";
			this->txt_R->Size = System::Drawing::Size(43, 20);
			this->txt_R->TabIndex = 6;
			// 
			// txt_G
			// 
			this->txt_G->Location = System::Drawing::Point(706, 22);
			this->txt_G->Name = L"txt_G";
			this->txt_G->Size = System::Drawing::Size(43, 20);
			this->txt_G->TabIndex = 6;
			// 
			// txt_B
			// 
			this->txt_B->Location = System::Drawing::Point(753, 22);
			this->txt_B->Name = L"txt_B";
			this->txt_B->Size = System::Drawing::Size(43, 20);
			this->txt_B->TabIndex = 6;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(621, 46);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(32, 13);
			this->label5->TabIndex = 5;
			this->label5->Text = L"YUV:";
			// 
			// txt_Y
			// 
			this->txt_Y->Location = System::Drawing::Point(660, 43);
			this->txt_Y->Name = L"txt_Y";
			this->txt_Y->Size = System::Drawing::Size(43, 20);
			this->txt_Y->TabIndex = 6;
			// 
			// txt_Cb
			// 
			this->txt_Cb->Location = System::Drawing::Point(706, 43);
			this->txt_Cb->Name = L"txt_Cb";
			this->txt_Cb->Size = System::Drawing::Size(43, 20);
			this->txt_Cb->TabIndex = 6;
			// 
			// txt_Cr
			// 
			this->txt_Cr->Location = System::Drawing::Point(753, 43);
			this->txt_Cr->Name = L"txt_Cr";
			this->txt_Cr->Size = System::Drawing::Size(43, 20);
			this->txt_Cr->TabIndex = 6;
			// 
			// checkBox_Pause
			// 
			this->checkBox_Pause->AutoSize = true;
			this->checkBox_Pause->Location = System::Drawing::Point(6, 22);
			this->checkBox_Pause->Name = L"checkBox_Pause";
			this->checkBox_Pause->Size = System::Drawing::Size(56, 17);
			this->checkBox_Pause->TabIndex = 1;
			this->checkBox_Pause->Text = L"Pause";
			this->checkBox_Pause->UseVisualStyleBackColor = true;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(364, 11);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(30, 13);
			this->label6->TabIndex = 2;
			this->label6->Text = L"Size:";
			// 
			// comboBox_imgsize
			// 
			this->comboBox_imgsize->FormattingEnabled = true;
			this->comboBox_imgsize->Items->AddRange(gcnew cli::array< System::Object^  >(4) {L"320x240", L"160x120", L"80x60", L"40x30"});
			this->comboBox_imgsize->Location = System::Drawing::Point(393, 8);
			this->comboBox_imgsize->Name = L"comboBox_imgsize";
			this->comboBox_imgsize->Size = System::Drawing::Size(72, 21);
			this->comboBox_imgsize->TabIndex = 3;
			this->comboBox_imgsize->Tag = L"";
			this->comboBox_imgsize->Text = L"320x240";
			this->comboBox_imgsize->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::comboBox1_SelectedIndexChanged);
			this->comboBox_imgsize->TextChanged += gcnew System::EventHandler(this, &MyForm::comboBox1_SelectedIndexChanged);
			// 
			// checkBox_process
			// 
			this->checkBox_process->AutoSize = true;
			this->checkBox_process->Location = System::Drawing::Point(6, 41);
			this->checkBox_process->Name = L"checkBox_process";
			this->checkBox_process->Size = System::Drawing::Size(113, 17);
			this->checkBox_process->TabIndex = 1;
			this->checkBox_process->Text = L"Enable processing";
			this->checkBox_process->UseVisualStyleBackColor = true;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(988, 619);
			this->Controls->Add(this->txt_Cr);
			this->Controls->Add(this->txt_B);
			this->Controls->Add(this->txt_Cb);
			this->Controls->Add(this->txt_V);
			this->Controls->Add(this->txt_G);
			this->Controls->Add(this->txt_Y);
			this->Controls->Add(this->txt_S);
			this->Controls->Add(this->txt_R);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->txt_H);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->comboBox_imgsize);
			this->Controls->Add(this->comboBox2);
			this->Controls->Add(this->comboBox1);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->lbl_fps);
			this->Controls->Add(this->checkBox_process);
			this->Controls->Add(this->checkBox_Pause);
			this->Controls->Add(this->checkBox1);
			this->Controls->Add(this->tableLayoutPanel1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->tableLayoutPanel1->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox4))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox5))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox6))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: 
		void show_image(Mat image, System::Windows::Forms::PictureBox^ pictureBox);
		System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e);
		System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e);
		System::Void timer2_Tick(System::Object^  sender, System::EventArgs^  e);
		System::Void pictureBox1_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);

		System::Void comboBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
		System::Void pictureBox1_DoubleClick(System::Object^  sender, System::EventArgs^  e);
		System::Void button1_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void backgroundWorker1_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e);
		System::Void pictureBox1_Click(System::Object^  sender, System::EventArgs^  e);
};
}
