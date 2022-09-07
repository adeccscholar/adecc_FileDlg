//---------------------------------------------------------------------------

#ifndef FileDlgFormFMXH
#define FileDlgFormFMXH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Edit.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.ListBox.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>

#include "FileDlgProcesses.h"
#include <memory>
#include <iostream>
#include <tuple>
#include <optional>
//---------------------------------------------------------------------------
class TfrmFileDlgFMX : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
   TLabel *lblDrives;
   TLabel *lblDirectories;
   TLabel *lblFiles;
   TLabel *lblFile;
   TComboBox *cbxDrives;
   TEdit *edtPath;
   TListBox *lbDirectories;
   TListBox *lbFiles;
   TEdit *edtFile;
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
   TMyForm         frm;
public:		// Benutzer-Deklarationen
   __fastcall TfrmFileDlgFMX(TFileDlgProcess& proc, TComponent* Owner);

};

//---------------------------------------------------------------------------
extern PACKAGE TfrmFileDlgFMX *frmFileDlgFMX;
//---------------------------------------------------------------------------
#endif
