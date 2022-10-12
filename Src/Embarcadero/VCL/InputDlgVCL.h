//---------------------------------------------------------------------------

#ifndef InputDlgVCLH
#define InputDlgVCLH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>
//---------------------------------------------------------------------------
class TfmInputVCL : public TForm
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
   __fastcall TfmInputVCL(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfmInputVCL *fmInputVCL;
//---------------------------------------------------------------------------
#endif
