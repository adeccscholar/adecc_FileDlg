//---------------------------------------------------------------------------

#ifndef UserDlgFMXH
#define UserDlgFMXH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Edit.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
//---------------------------------------------------------------------------
class TfrmUserDlgFMX : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
	TGroupBox *grpUser;
	TLabel *lblUser;
	TLabel *lblPassword;
	TEdit *edtUser;
	TEdit *edtPassword;
	TCheckBox *chbIntegrated;
	TButton *btnOk;
	TButton *btnCancel;
private:	// Benutzer-Deklarationen
public:		// Benutzer-Deklarationen
	__fastcall TfrmUserDlgFMX(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmUserDlgFMX *frmUserDlgFMX;
//---------------------------------------------------------------------------
#endif
