//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "InputDlgFMX.h"

#include "MyFileDlg.h"
#include "MyForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TfmInputFMX *fmInputFMX;
//---------------------------------------------------------------------------
__fastcall TfmInputFMX::TfmInputFMX(int pType, TComponent* Owner) : TForm(Owner) {
   iType = pType;
}
//---------------------------------------------------------------------------
void __fastcall TfmInputFMX::FormCreate(TObject *Sender) {
    if(iType != 0) {
       TMyForm frm(this, false);
       frm.Set<EMyFrameworkType::button>("btnSelect", "Auswahl");
       frm.ReadOnly<EMyFrameworkType::edit>("edtValue", true);
       }
    else {
       TMyForm frm(this, false);
       frm.Visible<EMyFrameworkType::button>("btnSelect", false);
       }


}
//---------------------------------------------------------------------------

void __fastcall TfmInputFMX::btnSelectClick(TObject *Sender) {
    if(iType != 0) {
       TMyForm frm(this, false);
       auto strPath = frm.Get<EMyFrameworkType::edit, std::string>("edtValue");
       auto [ret, mypath] = TMyFileDlg::SelectWithFileDirDlg(frm.Get<EMyFrameworkType::edit, std::string>("edtValue"), true);
       if (ret == EMyRetResults::ok) frm.Set<EMyFrameworkType::edit>("edtValue", mypath);
       }   
   }
//---------------------------------------------------------------------------

