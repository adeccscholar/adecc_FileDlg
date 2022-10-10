#include "MessageDlgClass.h"

MessageDlgClass::MessageDlgClass(QWidget *parent)
    : QDialog(parent)
{
    ui.setupUi(this);
    connect(ui.btnOk, &QPushButton::clicked, this, [this]() { accept(); });
    connect(ui.btnCancel, &QPushButton::clicked, this, [this]() { reject(); });
    connect(ui.btnNo, &QPushButton::clicked, this, [this]() { done(3); });
}

MessageDlgClass::~MessageDlgClass()
{}
