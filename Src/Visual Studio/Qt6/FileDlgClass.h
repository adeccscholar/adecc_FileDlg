#pragma once
#include "FileDlgProcesses.h"

#include <QDialog>
#include "ui_FileDlgClass.h"
#include <BuildFileDlg.h>

class MyFileLibAPI FileDlgClass : public QDialog
{
    Q_OBJECT

public:
    FileDlgClass(TFileDlgProcess& proc, QWidget *parent = Q_NULLPTR);
    ~FileDlgClass();

private:
    Ui::FileDlgClass ui;

    TFileDlgProcess& process;
    bool boEventsStarted = false;
    TMyForm         frm;

};
