//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "InputDlgVCL.h"

#include "MyFileDlg.h"
#include "MyForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmInputVCL *fmInputVCL;

// 969   / 840
//---------------------------------------------------------------------------
__fastcall TfmInputVCL::TfmInputVCL(int pType, TComponent* Owner)
   : TForm(Owner)
{
   iType = pType;
}
//---------------------------------------------------------------------------
void __fastcall TfmInputVCL::FormCreate(TObject *Sender) {
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

void __fastcall TfmInputVCL::btnSelectClick(TObject *Sender) {
    if(iType != 0) {
       TMyForm frm(this, false);
       auto strPath = frm.Get<EMyFrameworkType::edit, std::string>("edtValue");
       auto [ret, mypath] = TMyFileDlg::SelectWithFileDirDlg(frm.Get<EMyFrameworkType::edit, std::string>("edtValue"), true);
       if (ret == EMyRetResults::ok) frm.Set<EMyFrameworkType::edit>("edtValue", mypath);
       }
   }
   

//---------------------------------------------------------------------------

