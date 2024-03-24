#pragma once

#include <QDialog>
#include <QLabel>
#include "ui_UserDlg.h"

class UserDlg : public QDialog
{
    Q_OBJECT

public:
    UserDlg(QWidget *parent = nullptr);
    ~UserDlg();

private:
    Ui::UserDlgClass ui;
};
