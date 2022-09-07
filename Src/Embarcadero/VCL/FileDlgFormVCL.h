//---------------------------------------------------------------------------

#ifndef FileDlgFormVCLH
#define FileDlgFormVCLH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>

#include "FileDlgProcesses.h"
#include <memory>
#include <iostream>
#include <tuple>
#include <optional>
//---------------------------------------------------------------------------
class TfrmFileDlg : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
   TComboBox *cbxDrives;
   TEdit *edtPath;
   TListBox *lbFiles;
   TEdit *edtFile;
   TLabel *lblDirectories;
   TLabel *lblFiles;
   TLabel *lblDrives;
   TLabel *lblFile;
   TListBox *lbDirectories;
   TButton *btnOk;
   TButton *btnCancel;
   void __fastcall FormCreate(TObject *Sender);
   void __fastcall cbxDrivesChange(TObject *Sender);
   void __fastcall lbDirectoriesDblClick(TObject *Sender);
   void __fastcall lbFilesDblClick(TObject *Sender);
   void __fastcall btnOkClick(TObject *Sender);
   void __fastcall btnCancelClick(TObject *Sender);
private:	// Benutzer-Deklarationen
   TFileDlgProcess& process;
   TMyForm          frm;
public:		// Benutzer-Deklarationen
   __fastcall TfrmFileDlg(TFileDlgProcess& proc, TComponent* Owner);
   };

//---------------------------------------------------------------------------
extern PACKAGE TfrmFileDlg *frmFileDlg;
//---------------------------------------------------------------------------
#endif

