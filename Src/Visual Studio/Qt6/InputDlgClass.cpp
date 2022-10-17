#include "InputDlgClass.h"
#include "MyForm.h"
#include "MyFileDlg.h"

InputDlgClass::InputDlgClass(int iType, QWidget *parent)
    : QDialog(parent)
{
    ui.setupUi(this);
    if(iType != 0) {
       TMyForm frm(this, false);
       frm.Set<EMyFrameworkType::button>("btnSelect", "Auswahl");
       frm.ReadOnly<EMyFrameworkType::edit>("edtValue", true);
  
       connect(ui.btnSelect, &QPushButton::clicked, this, [this]() { 
          TMyForm frm(this, false);
          auto strPath = frm.Get<EMyFrameworkType::edit, std::string>("edtValue");
          auto [ret, mypath] = TMyFileDlg::SelectWithFileDirDlg(frm.Get<EMyFrameworkType::edit, std::string>("edtValue"), true);
          if (ret == EMyRetResults::ok) frm.Set<EMyFrameworkType::edit>("edtValue", mypath);
          });
       }
    else {
       TMyForm frm(this, false);
       frm.Visible<EMyFrameworkType::button>("btnSelect", false);
       }
    connect(ui.btnOk, &QPushButton::clicked, this, [this]() { accept(); });
    connect(ui.btnCancel, &QPushButton::clicked, this, [this]() { reject(); });

}

InputDlgClass::~InputDlgClass()
{}
