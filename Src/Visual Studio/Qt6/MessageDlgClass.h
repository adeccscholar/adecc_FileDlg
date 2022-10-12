#pragma once

#include <QDialog>
#include "ui_MessageDlgClass.h"

enum class EMyMessageType : int;

class MessageDlgClass : public QDialog
{
    Q_OBJECT

public:
    MessageDlgClass(EMyMessageType paType, QWidget *parent = nullptr);
    ~MessageDlgClass();

private:
    Ui::MessageDlgClassClass ui;
};
