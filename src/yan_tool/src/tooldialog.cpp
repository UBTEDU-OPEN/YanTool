#include "tooldialog.h"
#include "ui_tooldialog.h"

#include <QHBoxLayout>
#include <QLayout>
#include <QMouseEvent>
#include <QDebug>

ToolDialog::ToolDialog(const QString& title, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ToolDialog),
    leftBtnPressed_(false)
{
    ui->setupUi(this);
    ui->title->setText(title);
    setModal(true);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    setAttribute(Qt::WA_DeleteOnClose);
    auto contentLayout = new QHBoxLayout;
    contentLayout->setContentsMargins(0,0,0,0);
    ui->contentWidget->setLayout(contentLayout);
}

ToolDialog::~ToolDialog()
{
    delete ui;
}

void ToolDialog::setDisplayWidget(QWidget *displayWidget)
{
    ui->contentWidget->layout()->addWidget(displayWidget);
}

void ToolDialog::on_closeBtn_clicked()
{
    close();
}

void ToolDialog::mousePressEvent(QMouseEvent *event)
{
    auto pos = event->pos();
    if(event->button() == Qt::LeftButton && ui->titleWidget->geometry().contains(pos)) {
        leftBtnPressed_ = true;
        lastPos_ = mapToParent(pos);
    }
}

void ToolDialog::mouseMoveEvent(QMouseEvent *event)
{
    if(leftBtnPressed_) {
        auto currentPos = mapToParent(event->pos());
        QPoint position = pos() + currentPos - lastPos_;
        lastPos_ = currentPos;
        move(position.x(), position.y());
    }
}

void ToolDialog::mouseReleaseEvent(QMouseEvent *event)
{
    if(leftBtnPressed_) {
        leftBtnPressed_ = false;
    }
}
