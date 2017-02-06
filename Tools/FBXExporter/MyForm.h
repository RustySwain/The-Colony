#pragma once

namespace FBXExporter {

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
	public:
		MyForm(void)
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
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	protected:
	private: System::Windows::Forms::TextBox^  FBXPath;
	private: System::Windows::Forms::Button^  FileBrowser;
	private: System::Windows::Forms::Button^  Export;

	private: System::Windows::Forms::CheckBox^  ExportMesh;
	private: System::Windows::Forms::CheckBox^  ExportAnim;
	private: System::Windows::Forms::OpenFileDialog^  openFBXFile;


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
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->FBXPath = (gcnew System::Windows::Forms::TextBox());
			this->FileBrowser = (gcnew System::Windows::Forms::Button());
			this->Export = (gcnew System::Windows::Forms::Button());
			this->ExportMesh = (gcnew System::Windows::Forms::CheckBox());
			this->ExportAnim = (gcnew System::Windows::Forms::CheckBox());
			this->openFBXFile = (gcnew System::Windows::Forms::OpenFileDialog());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(9, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(56, 15);
			this->label1->TabIndex = 0;
			this->label1->Text = L"FBX File:";
			// 
			// FBXPath
			// 
			this->FBXPath->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->FBXPath->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->FBXPath->Location = System::Drawing::Point(12, 32);
			this->FBXPath->Name = L"FBXPath";
			this->FBXPath->Size = System::Drawing::Size(313, 21);
			this->FBXPath->TabIndex = 1;
			// 
			// FileBrowser
			// 
			this->FileBrowser->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->FileBrowser->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->FileBrowser->Location = System::Drawing::Point(325, 31);
			this->FileBrowser->Name = L"FileBrowser";
			this->FileBrowser->Size = System::Drawing::Size(31, 23);
			this->FileBrowser->TabIndex = 2;
			this->FileBrowser->Text = L"...";
			this->FileBrowser->UseVisualStyleBackColor = true;
			this->FileBrowser->Click += gcnew System::EventHandler(this, &MyForm::FileBrowser_Click);
			// 
			// Export
			// 
			this->Export->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Export->Location = System::Drawing::Point(255, 281);
			this->Export->Name = L"Export";
			this->Export->Size = System::Drawing::Size(101, 26);
			this->Export->TabIndex = 3;
			this->Export->Text = L"Export";
			this->Export->UseVisualStyleBackColor = true;
			// 
			// ExportMesh
			// 
			this->ExportMesh->AutoSize = true;
			this->ExportMesh->Checked = true;
			this->ExportMesh->CheckState = System::Windows::Forms::CheckState::Checked;
			this->ExportMesh->Location = System::Drawing::Point(12, 61);
			this->ExportMesh->Name = L"ExportMesh";
			this->ExportMesh->Size = System::Drawing::Size(85, 17);
			this->ExportMesh->TabIndex = 4;
			this->ExportMesh->Text = L"Export Mesh";
			this->ExportMesh->UseVisualStyleBackColor = true;
			// 
			// ExportAnim
			// 
			this->ExportAnim->AutoSize = true;
			this->ExportAnim->Checked = true;
			this->ExportAnim->CheckState = System::Windows::Forms::CheckState::Checked;
			this->ExportAnim->Location = System::Drawing::Point(12, 84);
			this->ExportAnim->Name = L"ExportAnim";
			this->ExportAnim->Size = System::Drawing::Size(105, 17);
			this->ExportAnim->TabIndex = 5;
			this->ExportAnim->Text = L"Export Animation";
			this->ExportAnim->UseVisualStyleBackColor = true;
			// 
			// openFBXFile
			// 
			this->openFBXFile->FileName = L"openFBXFile";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(368, 319);
			this->Controls->Add(this->ExportAnim);
			this->Controls->Add(this->ExportMesh);
			this->Controls->Add(this->Export);
			this->Controls->Add(this->FileBrowser);
			this->Controls->Add(this->FBXPath);
			this->Controls->Add(this->label1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void FileBrowser_Click(System::Object^  sender, System::EventArgs^  e)
	{
		openFBXFile->Filter = "FBX File|*.fbx";
		openFBXFile->ShowDialog();
		FBXPath->Text = openFBXFile->FileName;
		
	}
	};
}
