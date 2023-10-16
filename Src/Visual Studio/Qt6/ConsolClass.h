#pragma once

#include <QWidget>
#include "ui_ConsolClass.h"

class ConsolClass : public QWidget
{
    Q_OBJECT

public:
    ConsolClass(QWidget *parent = nullptr);
    ~ConsolClass();

private:
    Ui::ConsolClassClass ui;
};
