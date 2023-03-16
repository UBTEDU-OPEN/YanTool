#include "recoverywidget.h"
#include "ui_recoverywidget.h"

#include <QTimer>
#include <thread>

#include "noticedialog.h"
#include "toastdialog.h"
#include "icontoastdialog.h"
#include "roshelper.h"

RecoveryWidget::RecoveryWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecoveryWidget),
    thread_(nullptr)
{
    ui->setupUi(this);
}

RecoveryWidget::~RecoveryWidget()
{
    delete ui;
}

void RecoveryWidget::on_pushButton_clicked()
{
    ui->pushButton->setEnabled(false);
    update();
    emit enterRestore();
    thread_ = new RecoveryThread(this);
    connect(thread_,&RecoveryThread::lightRestoreFinished,this,&RecoveryWidget::onRestoreFinished);
    thread_->start();
}

void RecoveryWidget::onRestoreFinished(int result)
{
    if(result == 0) {
        auto dialog = new IconToastDialog(tr("Restore success"),this);
        auto wnd = window();
        auto pos = wnd->geometry().topLeft();
        auto wndSize = wnd->size();
        pos.setX(pos.x() + (wndSize.width()-dialog->width())/2);
        pos.setY(pos.y() + (wndSize.height()-dialog->height())/2);
        dialog->move(pos);
        dialog->show();
    } else {
        auto dialog = new NoticeDialog(this);
        dialog->setText(tr("Service exception, lightweight recovery failed, please try again!"));
        auto wnd = window();
        dialog->move(wnd->geometry().topLeft());
        dialog->setFixedSize(wnd->size());
        dialog->show();
    }
    emit exitRestore();
    ui->pushButton->setEnabled(true);
    update();
}
