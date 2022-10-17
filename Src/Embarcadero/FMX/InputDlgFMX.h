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
   TButton *btnSelect;
   void __fastcall FormCreate(TObject *Sender);
   void __fastcall btnSelectClick(TObject *Sender);
private:	// Benutzer-Deklarationen
   int iType = 0;
public:		// Benutzer-Deklarationen
   __fastcall TfmInputFMX(int = 0, TComponent* Owner = nullptr);
};
//---------------------------------------------------------------------------
extern PACKAGE TfmInputFMX *fmInputFMX;
//---------------------------------------------------------------------------
#endif
