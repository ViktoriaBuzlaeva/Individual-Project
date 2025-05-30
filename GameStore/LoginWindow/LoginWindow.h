// Copyright 2025 Viktoria Buzlaeva

#pragma once

namespace CppCLRWinFormsProject {

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

/// <summary>
/// Summary for LoginWindow
/// </summary>
public ref class LoginWindow : public System::Windows::Forms::Form {
 public:
    LoginWindow(void) {
        InitializeComponent();
    }

 protected:
    /// <summary>
    /// Clean up any resources being used.
    /// </summary>
    ~LoginWindow() {
        if (components) {
            delete components;
        }
    }
private: System::Windows::Forms::Label^ label1;
private: System::Windows::Forms::TextBox^ PasswordBox;
private: System::Windows::Forms::TextBox^ LoginBox;
private: System::Windows::Forms::Button^ SignInButton;
private: System::Windows::Forms::Label^ label3;
private: System::Windows::Forms::Label^ label2;
protected:
private:
    /// <summary>
    /// Required designer variable.
    /// </summary>
    System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
    /// <summary>
    /// Required method for Designer support - do not modify
    /// the contents of this method with the code editor.
    /// </summary>
    void InitializeComponent(void) {
        this->label1 = (gcnew System::Windows::Forms::Label());
        this->PasswordBox = (gcnew System::Windows::Forms::TextBox());
        this->LoginBox = (gcnew System::Windows::Forms::TextBox());
        this->SignInButton = (gcnew System::Windows::Forms::Button());
        this->label3 = (gcnew System::Windows::Forms::Label());
        this->label2 = (gcnew System::Windows::Forms::Label());
        this->SuspendLayout();
        //
        // label1
        //
        this->label1->AutoSize = true;
        this->label1->Font = (gcnew System::Drawing::Font
            (L"Microsoft Sans Serif", 48, System::Drawing::FontStyle::Regular,
            System::Drawing::GraphicsUnit::Point,
            static_cast<System::Byte>(204)));
        this->label1->Location = System::Drawing::Point(65, 9);
        this->label1->Name = L"label1";
        this->label1->Size = System::Drawing::Size(361, 73);
        this->label1->TabIndex = 0;
        this->label1->Text = L"GameStore";
        //
        // PasswordBox
        //
        this->PasswordBox->Font = (gcnew System::Drawing::Font
        (L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular,
            System::Drawing::GraphicsUnit::Point,
            static_cast<System::Byte>(204)));
        this->PasswordBox->Location = System::Drawing::Point(135, 160);
        this->PasswordBox->Name = L"PasswordBox";
        this->PasswordBox->Size = System::Drawing::Size(208, 31);
        this->PasswordBox->TabIndex = 2;
        //
        // LoginBox
        //
        this->LoginBox->Font = (gcnew System::Drawing::Font
            (L"Microsoft Sans Serif", 15.75F,
            System::Drawing::FontStyle::Regular,
            System::Drawing::GraphicsUnit::Point,
            static_cast<System::Byte>(204)));
        this->LoginBox->Location = System::Drawing::Point(135, 105);
        this->LoginBox->Name = L"LoginBox";
        this->LoginBox->Size = System::Drawing::Size(208, 31);
        this->LoginBox->TabIndex = 3;
        //
        // SignInButton
        //
        this->SignInButton->BackColor = System::Drawing::Color::White;
        this->SignInButton->Font = (gcnew System::Drawing::Font
            (L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular,
            System::Drawing::GraphicsUnit::Point,
            static_cast<System::Byte>(204)));
        this->SignInButton->Location = System::Drawing::Point(135, 210);
        this->SignInButton->Name = L"SignInButton";
        this->SignInButton->Size = System::Drawing::Size(208, 31);
        this->SignInButton->TabIndex = 4;
        this->SignInButton->Text = L"Sign in";
        this->SignInButton->UseVisualStyleBackColor = false;
        this->SignInButton->Click += gcnew System::EventHandler
            (this, &LoginWindow::SignInButton_Click);
        //
        // label3
        //
        this->label3->AutoSize = true;
        this->label3->Font = (gcnew System::Drawing::Font
            (L"Microsoft Sans Serif", 14.25F,
            System::Drawing::FontStyle::Regular,
            System::Drawing::GraphicsUnit::Point,
            static_cast<System::Byte>(204)));
        this->label3->Location = System::Drawing::Point(131, 139);
        this->label3->Name = L"label3";
        this->label3->Size = System::Drawing::Size(92, 24);
        this->label3->TabIndex = 6;
        this->label3->Text = L"Password";
        //
        // label2
        //
        this->label2->AutoSize = true;
        this->label2->BackColor = System::Drawing::Color::LightGray;
        this->label2->Font = (gcnew System::Drawing::Font
            (L"Microsoft Sans Serif", 14.25F,
            System::Drawing::FontStyle::Regular,
            System::Drawing::GraphicsUnit::Point,
            static_cast<System::Byte>(204)));
        this->label2->Location = System::Drawing::Point(131, 82);
        this->label2->Name = L"label2";
        this->label2->Size = System::Drawing::Size(57, 24);
        this->label2->TabIndex = 8;
        this->label2->Text = L"Login";
        //
        // LoginWindow
        //
        this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
        this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
        this->BackColor = System::Drawing::Color::LightGray;
        this->ClientSize = System::Drawing::Size(484, 261);
        this->Controls->Add(this->SignInButton);
        this->Controls->Add(this->LoginBox);
        this->Controls->Add(this->PasswordBox);
        this->Controls->Add(this->label1);
        this->Controls->Add(this->label3);
        this->Controls->Add(this->label2);
        this->Name = L"LoginWindow";
        this->StartPosition =
            System::Windows::Forms::FormStartPosition::CenterScreen;
        this->Text = L"LoginWindow";
        this->ResumeLayout(false);
        this->PerformLayout();
    }
#pragma endregion
private: System::Void SignInButton_Click
       (System::Object^ sender, System::EventArgs^ e) {
    MessageBox::Show("You are signed in!");
    this->Close();
}
};
}  // namespace CppCLRWinFormsProject
