#pragma once

#include <QDialog>
#include "ui_DirectoryDlgClass.h"
#include "MyForm.h"

class TFileDlgProcess;

class DirectoryDlgClass : public QDialog
{
    Q_OBJECT

public:
    DirectoryDlgClass(TFileDlgProcess& proc, QWidget *parent = nullptr);
    ~DirectoryDlgClass();

private:
    Ui::DirectoryDlgClassClass ui;

    TFileDlgProcess& process;
    bool boEventsStarted = false;
    TMyForm         frm;

};
