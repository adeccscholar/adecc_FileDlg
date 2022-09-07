#include "FileDlgClass.h"

FileDlgClass::FileDlgClass(TFileDlgProcess& proc, QWidget *parent)
    : process(proc), QDialog(parent) {
    ui.setupUi(this);
    frm.Set(this, false);

    connect(ui.cbxDrives,     SIGNAL(currentIndexChanged(int)), this, SLOT(DrivesChanged(int)));
    connect(ui.lbDirectories, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(DirectoriesDblClick(QListWidgetItem*)));
    connect(ui.lbFiles,       SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(FilesDblClick(QListWidgetItem*)));
    connect(ui.lbFiles,       SIGNAL(currentRowChanged(int)), this, SLOT(FilesChange(int)));
    connect(ui.btnOk,         SIGNAL(clicked()), this, SLOT(FinishEvent()));
    connect(ui.btnCancel,     SIGNAL(clicked()), this, SLOT(CancelEvent()));
    boEventsStarted = true;
   }


FileDlgClass::~FileDlgClass() {
   }


void FileDlgClass::DrivesChanged(int index) {
   if(boEventsStarted) process.ChangeDrives(frm);
   }

void FileDlgClass::FilesChange(int currentRow) {
   if (boEventsStarted) process.ChangeFiles(frm);
}

void FileDlgClass::DirectoriesDblClick(QListWidgetItem* item) {
   if(boEventsStarted) process.ClickDirectory(frm);
}

void FileDlgClass::FilesDblClick(QListWidgetItem* item) {
   if (boEventsStarted) {
      process.ChangeFiles(frm);
      accept();
      }
   }


void FileDlgClass::FinishEvent(void) {
   if (process.Execute(frm)) accept();
   }

void FileDlgClass::CancelEvent(void) {
   reject();
   }
//----