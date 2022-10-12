//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "MessageDlgFMX.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TfrmMessageDlgFMX *frmMessageDlgFMX;
//---------------------------------------------------------------------------
__fastcall TfrmMessageDlgFMX::TfrmMessageDlgFMX(EMyMessageType paType, TComponent* Owner)
   : TForm(Owner)
{
msgType    = paType;


}
//---------------------------------------------------------------------------
void __fastcall TfrmMessageDlgFMX::FormCreate(TObject *Sender)
{
   for(auto val : { imgInformation, imgWarning, imgError, imgQuestion }) val->Visible = false; 
   switch(msgType) {
      case EMyMessageType::information:
         imgInformation->Visible = true;;
         break;
      case EMyMessageType::warning:
         imgWarning->Visible = true;
         break;
      case EMyMessageType::error:
        imgError->Visible = true;
        break;
      case EMyMessageType::question:
         imgQuestion->Visible = true;
         break;
      default: 
         throw std::runtime_error("unerwarter Messagetyp");
      }
}
//---------------------------------------------------------------------------

