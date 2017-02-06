#pragma once
#include "FBXExporterTool.h"

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
	private: System::Windows::Forms::Label^  FBXFile_Label;
	protected:
	private: System::Windows::Forms::TextBox^  FBXPath;
	private: System::Windows::Forms::Button^  FileBrowser;
	private: System::Windows::Forms::Button^  Export;
	private: System::Windows::Forms::CheckBox^  ExportMesh;
	private: System::Windows::Forms::CheckBox^  ExportAnim;
	private: System::Windows::Forms::OpenFileDialog^  FBXDialog;
	public: System::Windows::Forms::RichTextBox^  ResultBox;
	private: System::Windows::Forms::CheckBox^  ExportAsBinary;
	public:
	private:




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
			this->FBXFile_Label = (gcnew System::Windows::Forms::Label());
			this->FBXPath = (gcnew System::Windows::Forms::TextBox());
			this->FileBrowser = (gcnew System::Windows::Forms::Button());
			this->Export = (gcnew System::Windows::Forms::Button());
			this->ExportMesh = (gcnew System::Windows::Forms::CheckBox());
			this->ExportAnim = (gcnew System::Windows::Forms::CheckBox());
			this->FBXDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->ResultBox = (gcnew System::Windows::Forms::RichTextBox());
			this->ExportAsBinary = (gcnew System::Windows::Forms::CheckBox());
			this->SuspendLayout();
			// 
			// FBXFile_Label
			// 
			this->FBXFile_Label->AutoSize = true;
			this->FBXFile_Label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->FBXFile_Label->Location = System::Drawing::Point(9, 9);
			this->FBXFile_Label->Name = L"FBXFile_Label";
			this->FBXFile_Label->Size = System::Drawing::Size(84, 15);
			this->FBXFile_Label->TabIndex = 0;
			this->FBXFile_Label->Text = L"FBX File Path:";
			// 
			// FBXPath
			// 
			this->FBXPath->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->FBXPath->Location = System::Drawing::Point(12, 30);
			this->FBXPath->Name = L"FBXPath";
			this->FBXPath->Size = System::Drawing::Size(363, 21);
			this->FBXPath->TabIndex = 1;
			// 
			// FileBrowser
			// 
			this->FileBrowser->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->FileBrowser->Location = System::Drawing::Point(374, 29);
			this->FileBrowser->Name = L"FileBrowser";
			this->FileBrowser->Size = System::Drawing::Size(39, 23);
			this->FileBrowser->TabIndex = 2;
			this->FileBrowser->Text = L"...";
			this->FileBrowser->UseVisualStyleBackColor = true;
			this->FileBrowser->Click += gcnew System::EventHandler(this, &MyForm::FileBrowser_Click);
			// 
			// Export
			// 
			this->Export->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->Export->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Export->Location = System::Drawing::Point(319, 300);
			this->Export->Name = L"Export";
			this->Export->Size = System::Drawing::Size(94, 30);
			this->Export->TabIndex = 3;
			this->Export->Text = L"Export";
			this->Export->UseVisualStyleBackColor = true;
			this->Export->Click += gcnew System::EventHandler(this, &MyForm::Export_Click);
			// 
			// ExportMesh
			// 
			this->ExportMesh->AutoSize = true;
			this->ExportMesh->Checked = true;
			this->ExportMesh->CheckState = System::Windows::Forms::CheckState::Checked;
			this->ExportMesh->Location = System::Drawing::Point(12, 59);
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
			this->ExportAnim->Location = System::Drawing::Point(12, 82);
			this->ExportAnim->Name = L"ExportAnim";
			this->ExportAnim->Size = System::Drawing::Size(105, 17);
			this->ExportAnim->TabIndex = 5;
			this->ExportAnim->Text = L"Export Animation";
			this->ExportAnim->UseVisualStyleBackColor = true;
			// 
			// FBXDialog
			// 
			this->FBXDialog->FileName = L"FBXDialog";
			// 
			// ResultBox
			// 
			this->ResultBox->Location = System::Drawing::Point(12, 134);
			this->ResultBox->Name = L"ResultBox";
			this->ResultBox->ReadOnly = true;
			this->ResultBox->Size = System::Drawing::Size(401, 160);
			this->ResultBox->TabIndex = 6;
			this->ResultBox->Text = L"Waiting for user...";
			// 
			// ExportAsBinary
			// 
			this->ExportAsBinary->AutoSize = true;
			this->ExportAsBinary->Location = System::Drawing::Point(12, 105);
			this->ExportAsBinary->Name = L"ExportAsBinary";
			this->ExportAsBinary->Size = System::Drawing::Size(101, 17);
			this->ExportAsBinary->TabIndex = 7;
			this->ExportAsBinary->Text = L"Export as binary";
			this->ExportAsBinary->UseVisualStyleBackColor = true;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(425, 342);
			this->Controls->Add(this->ExportAsBinary);
			this->Controls->Add(this->ResultBox);
			this->Controls->Add(this->ExportAnim);
			this->Controls->Add(this->ExportMesh);
			this->Controls->Add(this->Export);
			this->Controls->Add(this->FileBrowser);
			this->Controls->Add(this->FBXPath);
			this->Controls->Add(this->FBXFile_Label);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void FileBrowser_Click(System::Object^ sender, System::EventArgs^ e)
	{
		FBXDialog->Filter = "FBX File|*.fbx";
		FBXDialog->ShowDialog();
		FBXPath->Text = FBXDialog->FileName;
	}

	private: System::Void Export_Click(System::Object^ sender, System::EventArgs^ e)
	{
		const char* path = (const char*)(Runtime::InteropServices::Marshal::StringToHGlobalAnsi(FBXDialog->FileName)).ToPointer();
		FBXExporterTool fbxexport;

		if (FBXPath->Text == "")
		{
			ResultBox->AppendText("\nWhy are you trying to break my program?\n");
			ResultBox->AppendText("Select a .fbx file first!");
		}
		else
		{
			ResultBox->AppendText("\nExporting " + FBXDialog->FileName + "... ");
			fbxexport.Initialize();
			fbxexport.LoadScene(path, "exported\\", ExportMesh->Checked, ExportAnim->Checked, ExportAsBinary->Checked);
			fbxexport.ExportFBX();
			ResultBox->AppendText("Done!");
		}
	}
};
}
