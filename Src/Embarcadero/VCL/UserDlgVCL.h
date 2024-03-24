//---------------------------------------------------------------------------

#ifndef UserDlgVCLH
#define UserDlgVCLH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class TfrmUserDlgVCL : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
	TGroupBox *grpUser;
	TLabel *lblUser;
	TEdit *edtUser;
	TLabel *lblPassword;
	TEdit *edtPassword;
	TCheckBox *chbIntegrated;
	TButton *btnOk;
	TButton *btnCancel;
private:	// Benutzer-Deklarationen
public:		// Benutzer-Deklarationen
	__fastcall TfrmUserDlgVCL(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmUserDlgVCL *frmUserDlgVCL;
//---------------------------------------------------------------------------
#endif
