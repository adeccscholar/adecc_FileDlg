//---------------------------------------------------------------------------

#ifndef InputDlgFMXH
#define InputDlgFMXH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Objects.hpp>
#include <FMX.Types.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Edit.hpp>
//---------------------------------------------------------------------------
class TfmInputFMX : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
   TImage *Image1;
   TLabel *lblDescription;
   TEdit *edtValue;
   TLabel *lblRange;
   TButton *btnOk;
   TButton *btnCancel;
private:	// Benutzer-Deklarationen
public:		// Benutzer-Deklarationen
   __fastcall TfmInputFMX(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfmInputFMX *fmInputFMX;
//---------------------------------------------------------------------------
#endif
