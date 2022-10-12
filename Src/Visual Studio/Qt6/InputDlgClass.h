#pragma once

#include <QDialog>
#include "ui_InputDlgClass.h"

class InputDlgClass : public QDialog
{
    Q_OBJECT

public:
    InputDlgClass(QWidget *parent = nullptr);
    ~InputDlgClass();

private:
    Ui::InputDlgClassClass ui;
};
