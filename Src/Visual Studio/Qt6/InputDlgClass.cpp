#include "InputDlgClass.h"

InputDlgClass::InputDlgClass(QWidget *parent)
    : QDialog(parent)
{
    ui.setupUi(this);

    connect(ui.btnOk, &QPushButton::clicked, this, [this]() { accept(); });
    connect(ui.btnCancel, &QPushButton::clicked, this, [this]() { reject(); });

}

InputDlgClass::~InputDlgClass()
{}
