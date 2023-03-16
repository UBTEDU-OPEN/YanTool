#include "custombutton.h"
#include "ui_custombutton.h"

#include <QPaintEvent>
#include <QPainter>
#include <QMouseEvent>
#include <QPixmap>

CustomButton::CustomButton(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CustomButton)
{
    ui->setupUi(this);
}

CustomButton::~CustomButton()
{
    delete ui;
}

void CustomButton::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(rect(),QPixmap(currentUrl_));
}

void CustomButton::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
        currentUrl_ = bgPressedUrl_;
        update();
    }
}

void CustomButton::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
        currentUrl_ = bgUrl_;
        emit btnClicked();
        update();
    }
}

void CustomButton::setBgUrl(QString url, QString pressedUrl)
{
    bgUrl_ = url;
    bgPressedUrl_ = pressedUrl;
    currentUrl_ = bgUrl_;
}

void CustomButton::setText(QString text)
{
    ui->label->setText(text);
}
