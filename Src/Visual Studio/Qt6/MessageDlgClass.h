#pragma once

#include <QDialog>
#include "ui_MessageDlgClass.h"

class MessageDlgClass : public QDialog
{
    Q_OBJECT

public:
    MessageDlgClass(QWidget *parent = nullptr);
    ~MessageDlgClass();

private:
    Ui::MessageDlgClassClass ui;
};
