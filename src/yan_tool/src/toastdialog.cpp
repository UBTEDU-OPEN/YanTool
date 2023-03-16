#include "toastdialog.h"
#include "ui_toastdialog.h"

#include <QTimer>

ToastDialog::ToastDialog(const QString& text, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ToastDialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_DeleteOnClose);
    setModal(true);
    ui->label->setText(text);

    QTimer::singleShot(3000,this,&ToastDialog::onTimeout);
}

ToastDialog::~ToastDialog()
{
    delete ui;
}

void ToastDialog::onTimeout()
{
    close();
}
