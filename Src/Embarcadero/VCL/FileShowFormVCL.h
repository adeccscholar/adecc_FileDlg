//---------------------------------------------------------------------------

#ifndef FileShowFormVCLH
#define FileShowFormVCLH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmFileShowVCL : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
   TMemo *memFile;
   TPanel *pnlCtrl;
   TButton *btnOk;
private:	// Benutzer-Deklarationen
public:		// Benutzer-Deklarationen
   __fastcall TfrmFileShowVCL(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmFileShowVCL *frmFileShowVCL;
//---------------------------------------------------------------------------
#endif
