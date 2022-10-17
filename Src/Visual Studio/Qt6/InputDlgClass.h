#pragma once

#include <QDialog>
#include "ui_InputDlgClass.h"



class InputDlgClass : public QDialog
{
    Q_OBJECT

public:
    InputDlgClass(int iType = 0, QWidget *parent = nullptr);
    ~InputDlgClass();

private:
    Ui::InputDlgClassClass ui;
};
