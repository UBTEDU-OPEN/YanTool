#include "noticedialog.h"
#include "ui_noticedialog.h"

#include <QMouseEvent>
#include <QTimer>
#include <QPainter>

NoticeDialog::NoticeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NoticeDialog)
{
    ui->setupUi(this);
    auto flags = windowFlags();
    setWindowFlags(flags | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_DeleteOnClose);
    setModal(true);
}

NoticeDialog::~NoticeDialog()
{
    delete ui;
}

void NoticeDialog::on_ok_clicked()
{
    close();
}

void NoticeDialog::setText(const QString& text)
{
    ui->warningMsg->setText(text);
}
