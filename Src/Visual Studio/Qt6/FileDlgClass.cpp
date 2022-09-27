#include "FileDlgClass.h"

FileDlgClass::FileDlgClass(TFileDlgProcess& proc, QWidget *parent)
    : process(proc), QDialog(parent) {
    ui.setupUi(this);
    frm.Set(this, false);

    connect(ui.cbxDrives, &QComboBox::currentIndexChanged,        this, [this]() { if (boEventsStarted) this->process.ChangeDrives(frm); } );
    connect(ui.lbDirectories, &QListWidget::itemDoubleClicked,    this, [this]() { if (boEventsStarted) this->process.ClickDirectory(frm); });
    connect(ui.lbFiles,       &QListWidget::itemDoubleClicked,    this, [this]() { if (boEventsStarted) this->process.ChangeFiles(frm);
                                                                                   if (this->process.Execute(frm)) accept();
                                                                                 });
    connect(ui.lbFiles,       &QListWidget::itemSelectionChanged, this, [this]() { if (this->boEventsStarted) this->process.ChangeFiles(frm); });
    connect(ui.btnOk,         &QPushButton::clicked,              this, [this]() { if (this->process.Execute(frm)) accept(); });
    connect(ui.btnCancel,     &QPushButton::clicked,              this, [this]() { reject(); });
    boEventsStarted = true;
   }


FileDlgClass::~FileDlgClass() {
   }
