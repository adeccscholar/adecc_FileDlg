#include "DirectoryDlgClass.h"
#include "FileDlgProcesses.h"

DirectoryDlgClass::DirectoryDlgClass(TFileDlgProcess& proc, QWidget *parent)
    : process(proc), QDialog(parent)
{
    ui.setupUi(this);
    frm.Set(this, false);

    connect(ui.cbxDrives, &QComboBox::currentIndexChanged, this, [this]() { if (boEventsStarted) this->process.ChangeDrives(frm); });
    connect(ui.lbDirectories, &QListWidget::itemDoubleClicked, this, [this]() { if (boEventsStarted) this->process.ClickDirectory(frm); });

    connect(ui.btnOk, &QPushButton::clicked, this, [this]() { if (this->process.Execute(frm)) accept(); });
    connect(ui.btnCancel, &QPushButton::clicked, this, [this]() { reject(); });
    boEventsStarted = true;

}

DirectoryDlgClass::~DirectoryDlgClass()
{}
