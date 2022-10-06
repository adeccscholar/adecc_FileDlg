//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "DirectoryDlgFormVCL.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmDirectoryDlgVCL *frmDirectoryDlgVCL;
//---------------------------------------------------------------------------
__fastcall TfrmDirectoryDlgVCL::TfrmDirectoryDlgVCL(TFileDlgProcess& proc, TComponent* Owner)
   : process(proc), TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmDirectoryDlgVCL::cbxDrivesChange(TObject *Sender) {
   process.ChangeDrives(frm);
   }
//---------------------------------------------------------------------------
void __fastcall TfrmDirectoryDlgVCL::lbDirectoriesDblClick(TObject *Sender) {
   process.ClickDirectory(frm);
   }

//---------------------------------------------------------------------------
void __fastcall TfrmDirectoryDlgVCL::btnOkClick(TObject *Sender)
{
   if(process.Execute(frm)) ModalResult = mrOk;
   else ModalResult = mrNone;
   
}
//---------------------------------------------------------------------------
void __fastcall TfrmDirectoryDlgVCL::btnCancelClick(TObject *Sender)
{
   ModalResult = mrCancel;
   
}
//---------------------------------------------------------------------------
