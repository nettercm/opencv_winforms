#pragma once

extern double canny_t1,canny_t2;
extern unsigned char h_min,h_max,s_min,s_max,v_min,v_max;

namespace opencv_winforms {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for settings_dialog
	/// </summary>
	public ref class settings_dialog : public System::Windows::Forms::Form
	{
	public:
		settings_dialog(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~settings_dialog()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TabControl^  tabControl1;
	protected: 
	private: System::Windows::Forms::TabPage^  tabPage1;
	private: System::Windows::Forms::TabPage^  tabPage2;
	private: System::Windows::Forms::TrackBar^  trackBar_edge_t1;

	private: System::Windows::Forms::ComboBox^  comboBox_edge_t1;

	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::ComboBox^  comboBox_edge_t2;
	private: System::Windows::Forms::TrackBar^  trackBar_edge_t2;
	private: System::Windows::Forms::Button^  button_clear_hsv_min_max;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->comboBox_edge_t2 = (gcnew System::Windows::Forms::ComboBox());
			this->comboBox_edge_t1 = (gcnew System::Windows::Forms::ComboBox());
			this->trackBar_edge_t2 = (gcnew System::Windows::Forms::TrackBar());
			this->trackBar_edge_t1 = (gcnew System::Windows::Forms::TrackBar());
			this->button_clear_hsv_min_max = (gcnew System::Windows::Forms::Button());
			this->tabControl1->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->tabPage2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar_edge_t2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar_edge_t1))->BeginInit();
			this->SuspendLayout();
			// 
			// tabControl1
			// 
			this->tabControl1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Controls->Add(this->tabPage2);
			this->tabControl1->Location = System::Drawing::Point(1, 1);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(562, 349);
			this->tabControl1->TabIndex = 0;
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->button_clear_hsv_min_max);
			this->tabPage1->Location = System::Drawing::Point(4, 22);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(554, 323);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"Color blob detection";
			this->tabPage1->UseVisualStyleBackColor = true;
			// 
			// tabPage2
			// 
			this->tabPage2->Controls->Add(this->label2);
			this->tabPage2->Controls->Add(this->label1);
			this->tabPage2->Controls->Add(this->comboBox_edge_t2);
			this->tabPage2->Controls->Add(this->comboBox_edge_t1);
			this->tabPage2->Controls->Add(this->trackBar_edge_t2);
			this->tabPage2->Controls->Add(this->trackBar_edge_t1);
			this->tabPage2->Location = System::Drawing::Point(4, 22);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(3);
			this->tabPage2->Size = System::Drawing::Size(554, 323);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"Edge detection";
			this->tabPage2->UseVisualStyleBackColor = true;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(7, 63);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(94, 18);
			this->label2->TabIndex = 2;
			this->label2->Text = L"Threashold 2";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(7, 3);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(94, 18);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Threashold 1";
			// 
			// comboBox_edge_t2
			// 
			this->comboBox_edge_t2->FormattingEnabled = true;
			this->comboBox_edge_t2->Items->AddRange(gcnew cli::array< System::Object^  >(10) {L"1", L"10", L"20", L"30", L"40", L"50", 
				L"100", L"150", L"200", L"250"});
			this->comboBox_edge_t2->Location = System::Drawing::Point(7, 87);
			this->comboBox_edge_t2->Name = L"comboBox_edge_t2";
			this->comboBox_edge_t2->Size = System::Drawing::Size(91, 21);
			this->comboBox_edge_t2->TabIndex = 1;
			this->comboBox_edge_t2->Text = L"1";
			// 
			// comboBox_edge_t1
			// 
			this->comboBox_edge_t1->FormattingEnabled = true;
			this->comboBox_edge_t1->Items->AddRange(gcnew cli::array< System::Object^  >(10) {L"1", L"10", L"20", L"30", L"40", L"50", 
				L"100", L"150", L"200", L"250"});
			this->comboBox_edge_t1->Location = System::Drawing::Point(7, 27);
			this->comboBox_edge_t1->Name = L"comboBox_edge_t1";
			this->comboBox_edge_t1->Size = System::Drawing::Size(91, 21);
			this->comboBox_edge_t1->TabIndex = 1;
			this->comboBox_edge_t1->Text = L"1";
			this->comboBox_edge_t1->SelectedIndexChanged += gcnew System::EventHandler(this, &settings_dialog::comboBox_edge_t1_TextUpdate);
			this->comboBox_edge_t1->TextUpdate += gcnew System::EventHandler(this, &settings_dialog::comboBox_edge_t1_TextUpdate);
			// 
			// trackBar_edge_t2
			// 
			this->trackBar_edge_t2->LargeChange = 10;
			this->trackBar_edge_t2->Location = System::Drawing::Point(104, 63);
			this->trackBar_edge_t2->Maximum = 255;
			this->trackBar_edge_t2->Name = L"trackBar_edge_t2";
			this->trackBar_edge_t2->Size = System::Drawing::Size(442, 45);
			this->trackBar_edge_t2->TabIndex = 0;
			// 
			// trackBar_edge_t1
			// 
			this->trackBar_edge_t1->LargeChange = 10;
			this->trackBar_edge_t1->Location = System::Drawing::Point(104, 3);
			this->trackBar_edge_t1->Maximum = 255;
			this->trackBar_edge_t1->Name = L"trackBar_edge_t1";
			this->trackBar_edge_t1->Size = System::Drawing::Size(442, 45);
			this->trackBar_edge_t1->TabIndex = 0;
			this->trackBar_edge_t1->Scroll += gcnew System::EventHandler(this, &settings_dialog::trackBar_edge_t1_Scroll);
			// 
			// button_clear_hsv_min_max
			// 
			this->button_clear_hsv_min_max->Location = System::Drawing::Point(7, 6);
			this->button_clear_hsv_min_max->Name = L"button_clear_hsv_min_max";
			this->button_clear_hsv_min_max->Size = System::Drawing::Size(121, 23);
			this->button_clear_hsv_min_max->TabIndex = 0;
			this->button_clear_hsv_min_max->Text = L"Clear HSV min/max";
			this->button_clear_hsv_min_max->UseVisualStyleBackColor = true;
			this->button_clear_hsv_min_max->Click += gcnew System::EventHandler(this, &settings_dialog::button_clear_hsv_min_max_Click);
			// 
			// settings_dialog
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(563, 351);
			this->Controls->Add(this->tabControl1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::SizableToolWindow;
			this->Name = L"settings_dialog";
			this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Show;
			this->Text = L"settings_dialog";
			this->TopMost = true;
			this->tabControl1->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->tabPage2->ResumeLayout(false);
			this->tabPage2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar_edge_t2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar_edge_t1))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void comboBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			 }
private: System::Void trackBar_edge_t1_Scroll(System::Object^  sender, System::EventArgs^  e) {
			 comboBox_edge_t1->Text = trackBar_edge_t1->Value.ToString();
			 canny_t1 = canny_t2 = trackBar_edge_t1->Value;
		 }
private: System::Void comboBox_edge_t1_TextUpdate(System::Object^  sender, System::EventArgs^  e) {
			 trackBar_edge_t1->Value = Convert::ToInt32(comboBox_edge_t1->Text);
			 trackBar_edge_t1->Update();
 			 canny_t1 = canny_t2 = trackBar_edge_t1->Value;

		 }
private: System::Void button_clear_hsv_min_max_Click(System::Object^  sender, System::EventArgs^  e) {
			 h_min=s_min=v_min=255;
			 h_max=s_max=v_max=0;
		 }
};
}
