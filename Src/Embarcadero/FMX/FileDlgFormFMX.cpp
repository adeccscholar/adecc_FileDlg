//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "FileDlgFormFMX.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TfrmFileDlgFMX *frmFileDlgFMX;
//---------------------------------------------------------------------------
__fastcall TfrmFileDlgFMX::TfrmFileDlgFMX(TFileDlgProcess& proc, TComponent* Owner)
   : process(proc), TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmFileDlgFMX::FormCreate(TObject *Sender) {
   frm.Set(this, false);
   }
//---------------------------------------------------------------------------
void __fastcall TfrmFileDlgFMX::cbxDrivesChange(TObject *Sender) {
   if(process.FireMessages()) process.ChangeDrives(frm);
   }
//---------------------------------------------------------------------------
void __fastcall TfrmFileDlgFMX::lbDirectoriesDblClick(TObject *Sender) {
   process.ClickDirectory(frm);
   }
//---------------------------------------------------------------------------
void __fastcall TfrmFileDlgFMX::lbFilesDblClick(TObject *Sender) {
   process.ChangeFiles(frm);
   ModalResult = mrOk;
   }
//---------------------------------------------------------------------------
void __fastcall TfrmFileDlgFMX::btnOkClick(TObject *Sender) {
   if(process.Execute(frm)) ModalResult = mrOk;
   else ModalResult = mrNone;
   }
//---------------------------------------------------------------------------
void __fastcall TfrmFileDlgFMX::btnCancelClick(TObject *Sender) {
   ModalResult = mrCancel;
   }
//---------------------------------------------------------------------------
