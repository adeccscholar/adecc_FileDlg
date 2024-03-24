//---------------------------------------------------------------------------

#ifndef MessageDlgH
#define MessageDlgH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.BaseImageCollection.hpp>
#include <Vcl.ImageCollection.hpp>
#include <Vcl.VirtualImage.hpp>
#include <Vcl.ComCtrls.hpp>
//---------------------------------------------------------------------------
#include <adecc_Scholar\MyStdTypes.h>
#include <Vcl.BaseImageCollection.hpp>
#include <Vcl.ImageCollection.hpp>
#include <Vcl.VirtualImage.hpp>

class TfrmMessage : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
   TMemo *memMessage;
   TPanel *Panel1;
   TPanel *Panel2;
   TButton *btnOk;
   TButton *btnCancel;
   TButton *btnNo;
   TImageCollection *lstImages;
   TVirtualImage *imgVirtualSymbol;
	TPageControl *PageControl1;
	TTabSheet *tabMessage;
	TTabSheet *tabDetails;
	TMemo *memDetails;
   void __fastcall FormCreate(TObject *Sender);
private:	// Benutzer-Deklarationen
   EMyMessageType msgType;
public:		// Benutzer-Deklarationen
   __fastcall TfrmMessage(EMyMessageType paType, TComponent* Owner = nullptr);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMessage *frmMessage;
//---------------------------------------------------------------------------
#endif
