//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop


#include "MessageDlg.h"

#include <stdexcept>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmMessage *frmMessage;
//---------------------------------------------------------------------------
__fastcall TfrmMessage::TfrmMessage(EMyMessageType paType, TComponent* Owner) : TForm(Owner) {
   msgType    = paType;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMessage::FormCreate(TObject *Sender) {
   switch(msgType) {
      case EMyMessageType::information:
         imgVirtualSymbol->ImageIndex = 1;
         break;
      case EMyMessageType::warning:
         imgVirtualSymbol->ImageIndex = 3;
         break;
      case EMyMessageType::error:
         imgVirtualSymbol->ImageIndex = 0;
         btnCancel->Left = 256;
         break;
      case EMyMessageType::question:
         imgVirtualSymbol->ImageIndex = 2;
         break;
      default: 
         throw std::runtime_error("unerwarter Messagetyp");
      }
   
   }
//---------------------------------------------------------------------------

