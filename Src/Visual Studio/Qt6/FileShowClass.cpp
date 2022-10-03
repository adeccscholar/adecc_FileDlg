#include "FileShowClass.h"


FileShowClass::FileShowClass(QWidget *parent)
    : QDialog(parent)
{
    ui.setupUi(this);
    connect(ui.btnOk, &QPushButton::clicked, this, [this]() { this->close(); });
}

FileShowClass::~FileShowClass()
{}
