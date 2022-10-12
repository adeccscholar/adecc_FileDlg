//---------------------------------------------------------------------------

#ifndef MessageDlgFMXH
#define MessageDlgFMXH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.ImgList.hpp>
#include <System.ImageList.hpp>
#include <FMX.Objects.hpp>
#include <FMX.Types.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Memo.hpp>
#include <FMX.Memo.Types.hpp>
#include <FMX.ScrollBox.hpp>
#include <FMX.StdCtrls.hpp>
//---------------------------------------------------------------------------
#include "MyStdTypes.h"

class TfrmMessageDlgFMX : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
   TMemo *memMessage;
   TButton *btnOk;
   TButton *btnNo;
   TButton *btnCancel;
   TPanel *pnlBottom;
   TImage *imgInformation;
   TImage *imgWarning;
   TImage *imgError;
   TImage *imgQuestion;
   void __fastcall FormCreate(TObject *Sender);
private:	// Benutzer-Deklarationen
   EMyMessageType msgType;
public:		// Benutzer-Deklarationen
   __fastcall TfrmMessageDlgFMX(EMyMessageType paType, TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMessageDlgFMX *frmMessageDlgFMX;
//---------------------------------------------------------------------------
#endif
