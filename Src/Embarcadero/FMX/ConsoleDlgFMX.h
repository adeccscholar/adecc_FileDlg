//---------------------------------------------------------------------------

#ifndef ConsoleDlgFMXH
#define ConsoleDlgFMXH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Memo.hpp>
#include <FMX.Memo.Types.hpp>
#include <FMX.ScrollBox.hpp>
#include <FMX.Types.hpp>
//---------------------------------------------------------------------------
class TfrmConsoleDlgFMX : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
	TMemo *memText;
private:	// Benutzer-Deklarationen
public:		// Benutzer-Deklarationen
	__fastcall TfrmConsoleDlgFMX(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmConsoleDlgFMX *frmConsoleDlgFMX;
//---------------------------------------------------------------------------
#endif
