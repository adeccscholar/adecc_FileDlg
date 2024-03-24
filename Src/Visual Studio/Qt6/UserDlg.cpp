#include "UserDlg.h"
#include <QWidget>
#include <QLabel> 


UserDlg::UserDlg(QWidget *parent)
    : QDialog(parent)
{
    ui.setupUi(this);

    ui.lblUser->setBuddy(ui.edtUser);
    ui.edtPassword->setEchoMode(QLineEdit::Password);
    ui.edtPassword->setFocus();
    ui.lblPassword->setBuddy(ui.edtPassword);
 
    connect(ui.chbIntegrated, &QCheckBox::stateChanged, this, [this](int state) {
       if(state == Qt::Checked) {
          ui.edtUser->setEnabled(false);
          ui.edtPassword->setEnabled(false);
          }
       else {
          ui.edtUser->setEnabled(true);
          ui.edtPassword->setEnabled(true);
          }
       });

    connect(ui.btnOk,         &QPushButton::clicked, this, [this]() { accept(); });
    connect(ui.btnCancel,     &QPushButton::clicked, this, [this]() { reject(); });
}

UserDlg::~UserDlg()
{}
