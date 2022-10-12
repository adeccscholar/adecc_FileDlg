#include "MessageDlgClass.h"
#include "MyStdTypes.h"


MessageDlgClass::MessageDlgClass(EMyMessageType paType, QWidget *parent)
    : QDialog(parent) {
    ui.setupUi(this);

    switch(paType) {
       case EMyMessageType::information:
          {
          QImage image0(":/images/my_information.png");
          ui.lblImage->setPixmap(QPixmap::fromImage(image0));
          }
          break;
       case EMyMessageType::warning:
          {
          QImage image0(":/images/my_warning.png");
          ui.lblImage->setPixmap(QPixmap::fromImage(image0));
          }
          break;
       case EMyMessageType::error:
          {
          QImage image0(":/images/my_error.png");
          ui.lblImage->setPixmap(QPixmap::fromImage(image0));
          }
          break;
       case EMyMessageType::question:
          {
          QImage image0(":/images/my_question.png");
          ui.lblImage->setPixmap(QPixmap::fromImage(image0));
          }
          break;
       default:
          throw std::runtime_error("unerwarter Messagetyp");
       }

    connect(ui.btnOk, &QPushButton::clicked, this, [this]() { accept(); });
    connect(ui.btnCancel, &QPushButton::clicked, this, [this]() { reject(); });
    connect(ui.btnNo, &QPushButton::clicked, this, [this]() { done(3); });
   }

MessageDlgClass::~MessageDlgClass()
{}
