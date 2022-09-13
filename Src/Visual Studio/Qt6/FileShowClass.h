#pragma once

#include <QDialog>
#include "ui_FileShowClass.h"

class FileShowClass : public QDialog
{
    Q_OBJECT

public:
    FileShowClass(QWidget *parent = nullptr);
    ~FileShowClass();

private:
    Ui::FileShowClassClass ui;
};
