#include "icontoastdialog.h"
#include "ui_icontoastdialog.h"

#include <QTimer>

IconToastDialog::IconToastDialog(QString text, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IconToastDialog)
{
    ui->setupUi(this);
    ui->label_2->setText(text);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_DeleteOnClose);
    setModal(true);
    adjustSize();
    QTimer::singleShot(3000,this,&IconToastDialog::onTimeout);
}

IconToastDialog::~IconToastDialog()
{
    delete ui;
}

void IconToastDialog::onTimeout()
{
    close();
}
