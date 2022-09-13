//---------------------------------------------------------------------------

#ifndef FileShowDlgFMXH
#define FileShowDlgFMXH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Memo.hpp>
#include <FMX.Memo.Types.hpp>
#include <FMX.ScrollBox.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
//---------------------------------------------------------------------------
class TfrmFileShowDlg : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
   TPanel *Panel1;
   TButton *btnOk;
   TMemo *memFile;
private:	// Benutzer-Deklarationen
public:		// Benutzer-Deklarationen
   __fastcall TfrmFileShowDlg(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmFileShowDlg *frmFileShowDlg;
//---------------------------------------------------------------------------
#endif
