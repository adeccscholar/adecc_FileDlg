#pragma once
#include "FileDlgProcesses.h"

#include <QDialog>
#include "ui_FileDlgClass.h"

class FileDlgClass : public QDialog
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
