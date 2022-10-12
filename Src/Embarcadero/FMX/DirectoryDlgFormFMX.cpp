//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "DirectoryDlgFormFMX.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TfrmDirectoryDlgFMX *frmDirectoryDlgFMX;
//---------------------------------------------------------------------------
__fastcall TfrmDirectoryDlgFMX::TfrmDirectoryDlgFMX(TFileDlgProcess& proc, TComponent* Owner)
   : process(proc), TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmDirectoryDlgFMX::FormCreate(TObject *Sender)
{
frm.Set(this, false);   
}
//---------------------------------------------------------------------------
void __fastcall TfrmDirectoryDlgFMX::ComboBox1Change(TObject *Sender)
{
process.ChangeDrives(frm);   
}
//---------------------------------------------------------------------------
void __fastcall TfrmDirectoryDlgFMX::lbDirectoriesDblClick(TObject *Sender)
{
process.ClickDirectory(frm);   
}
//---------------------------------------------------------------------------
void __fastcall TfrmDirectoryDlgFMX::btnOkClick(TObject *Sender)
{
   if(process.Execute(frm)) ModalResult = mrOk;
   else ModalResult = mrNone;
}
//---------------------------------------------------------------------------
