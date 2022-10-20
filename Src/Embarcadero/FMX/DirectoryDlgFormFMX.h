//---------------------------------------------------------------------------

#ifndef DirectoryDlgFormFMXH
#define DirectoryDlgFormFMXH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <FMX.Edit.hpp>
#include <FMX.ListBox.hpp>
#include <FMX.Layouts.hpp>
//---------------------------------------------------------------------------
#include "FileDlgProcesses.h"

class TfrmDirectoryDlgFMX : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
   TPanel *pnlTop;
   TPanel *pnlCenter;
   TPanel *pnlBottom;
   TLabel *lblDrives;
   TLabel *lblPath;
   TLabel *lblDirectories;
   TComboBox *cbxDrives;
   TEdit *edtPath;
   TListBox *lbDirectories;
   TButton *btnOk;
   TButton *btnCancel;
   void __fastcall FormCreate(TObject *Sender);
   void __fastcall cbxDrivesChange(TObject *Sender);
   void __fastcall lbDirectoriesDblClick(TObject *Sender);
   void __fastcall btnOkClick(TObject *Sender);
private:	// Benutzer-Deklarationen
   TFileDlgProcess& process;
   TMyForm          frm;
public:		// Benutzer-Deklarationen
   __fastcall TfrmDirectoryDlgFMX(TFileDlgProcess& proc, TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmDirectoryDlgFMX *frmDirectoryDlgFMX;
//---------------------------------------------------------------------------
#endif
