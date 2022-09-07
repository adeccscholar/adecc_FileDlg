//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FileDlgFormVCL.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmFileDlg *frmFileDlg;
//---------------------------------------------------------------------------
__fastcall TfrmFileDlg::TfrmFileDlg(TFileDlgProcess& proc, TComponent* Owner) :  process(proc), TForm(Owner) {
   }

//---------------------------------------------------------------------------
void __fastcall TfrmFileDlg::FormCreate(TObject *Sender) {
   frm.Set(this, false);
   }
//---------------------------------------------------------------------------
void __fastcall TfrmFileDlg::cbxDrivesChange(TObject *Sender) {
   process.ChangeDrives(frm);
   }
//---------------------------------------------------------------------------
void __fastcall TfrmFileDlg::lbDirectoriesDblClick(TObject *Sender) {
   process.ClickDirectory(frm);
   }
//---------------------------------------------------------------------------
void __fastcall TfrmFileDlg::lbFilesDblClick(TObject *Sender) {
   process.ChangeFiles(frm);
   ModalResult = mrOk;
   }
//---------------------------------------------------------------------------
void __fastcall TfrmFileDlg::btnOkClick(TObject *Sender) {
   if(process.Execute(frm)) ModalResult = mrOk;
   else ModalResult = mrNone;
   }
//---------------------------------------------------------------------------
void __fastcall TfrmFileDlg::btnCancelClick(TObject *Sender) {
   ModalResult = mrCancel;
   }
//---------------------------------------------------------------------------
