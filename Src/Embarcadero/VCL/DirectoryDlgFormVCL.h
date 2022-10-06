//---------------------------------------------------------------------------

#ifndef DirectoryDlgFormVCLH
#define DirectoryDlgFormVCLH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
#include "FileDlgProcesses.h"
class TfrmDirectoryDlgVCL : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
   TPanel *Panel1;
   TPanel *Panel2;
   TListBox *lbDirectories;
   TButton *btnOk;
   TButton *btnCancel;
   TLabel *lblDrives;
   TLabel *Label2;
   TComboBox *cbxDrives;
   void __fastcall btnOkClick(TObject *Sender);
   void __fastcall btnCancelClick(TObject *Sender);
   void __fastcall lbDirectoriesDblClick(TObject *Sender);
   void __fastcall cbxDrivesChange(TObject *Sender);
private:	// Benutzer-Deklarationen
   TFileDlgProcess& process;
   TMyForm          frm;
public:		// Benutzer-Deklarationen
   __fastcall TfrmDirectoryDlgVCL(TFileDlgProcess& proc, TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmDirectoryDlgVCL *frmDirectoryDlgVCL;
//---------------------------------------------------------------------------
#endif
