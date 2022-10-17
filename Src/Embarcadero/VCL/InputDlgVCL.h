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
   TButton *btnSelect;
   void __fastcall FormCreate(TObject *Sender);
   void __fastcall btnSelectClick(TObject *Sender);
private:	// Benutzer-Deklarationen
   int iType = 0;
public:		// Benutzer-Deklarationen
   __fastcall TfmInputVCL(int pType, TComponent* Owner = nullptr);
};
//---------------------------------------------------------------------------
extern PACKAGE TfmInputVCL *fmInputVCL;
//---------------------------------------------------------------------------
#endif
