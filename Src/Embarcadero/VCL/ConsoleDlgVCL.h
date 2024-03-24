//---------------------------------------------------------------------------

#ifndef ConsoleDlgVCLH
#define ConsoleDlgVCLH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class TfrmConsoleDlgVCL : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
	TMemo *memText;
private:	// Benutzer-Deklarationen
public:		// Benutzer-Deklarationen
	__fastcall TfrmConsoleDlgVCL(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmConsoleDlgVCL *frmConsoleDlgVCL;
//---------------------------------------------------------------------------
#endif
