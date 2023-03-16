#include "uploadlogwidget.h"
#include "ui_uploadlogwidget.h"

#include <QDebug>
#include <QFile>
#include <QApplication>
#include <QTextCursor>

#include "toastdialog.h"
#include "noticedialog.h"
#include "roshelper.h"
#include "icontoastdialog.h"

const int kMaxTextLength = 1000;

UploadLogWidget::UploadLogWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UploadLogWidget),
    thread_(nullptr)
{
    ui->setupUi(this);
    ui->textEdit->setAcceptRichText(false);
    ui->textEdit->setPlaceholderText(tr("Problem type: Robot network connection failed\n" \
                                        "Steps to reproduce: 1. Click the system desktop network icon;" \
                                        " 2. Select the network and enter the correct password, but the network fails\n"
                                        "Time of occurrence: 2021-7-30 20:36\n"
                                        "Contact number: 15812345678"));
    connect(ui->textEdit,&QTextEdit::textChanged,this,&UploadLogWidget::onTextChanged);
    connect(ui->checkBox,&QCheckBox::stateChanged,this,&UploadLogWidget::onCheckStateChanged);
}

UploadLogWidget::~UploadLogWidget()
{
    delete ui;
}

void UploadLogWidget::on_pushButton_clicked()
{
    ui->pushButton->setEnabled(false);
    ui->textEdit->setEnabled(false);
    ui->checkBox->setCheckable(false);
    update();

    auto path = "/tmp/description.txt";
    QFile file(path);
    if(file.exists()) {
        file.remove();
    }

    if(file.open(QFile::WriteOnly)) {
        auto text = ui->textEdit->document()->toPlainText();
        file.write(text.toLocal8Bit());
        file.close();
    }
    emit enterUploadLog();
    thread_ = new UploadLogThread(this);
    connect(thread_,&UploadLogThread::uploadFinished,this,&UploadLogWidget::onUploadResult);
    thread_->start();
}

void UploadLogWidget::onTextChanged()
{
    bool isChecked = ui->checkBox->isChecked();
    auto text = ui->textEdit->document()->toPlainText();
    if(isChecked && !text.isEmpty()) {
        ui->pushButton->setEnabled(true);
    } else {
        ui->pushButton->setEnabled(false);
    }


    QString textContent = ui->textEdit->toPlainText();
    qint32 length = textContent.count();
    if(length > kMaxTextLength) {
        int position = ui->textEdit->textCursor().position();
        QTextCursor textCursor = ui->textEdit->textCursor();
        textContent.remove(position - (length - kMaxTextLength), length - kMaxTextLength);
        ui->textEdit->setText(textContent);
        textCursor.setPosition(position - (length - kMaxTextLength));
        ui->textEdit->setTextCursor(textCursor);
    }
}

void UploadLogWidget::onCheckStateChanged(int state)
{
    bool isChecked = ui->checkBox->isChecked();
    auto text = ui->textEdit->document()->toPlainText();
    if(isChecked && !text.isEmpty()) {
        ui->pushButton->setEnabled(true);
    } else {
        ui->pushButton->setEnabled(false);
    }
}

void UploadLogWidget::onUploadResult(int result)
{
    ui->pushButton->setEnabled(true);
    ui->textEdit->setEnabled(true);
    ui->checkBox->setCheckable(true);
    ui->checkBox->setChecked(true);
    if(result == 0) {
        auto dialog = new IconToastDialog(tr("Uploaded successfully"),this);
        auto wnd = window();
        auto pos = wnd->geometry().topLeft();
        auto wndSize = wnd->size();
        pos.setX(pos.x() + (wndSize.width()-dialog->width())/2);
        pos.setY(pos.y() + (wndSize.height()-dialog->height())/2);
        dialog->move(pos);
        dialog->show();
    } else {
        auto dialog = new NoticeDialog(this);
        if(result == -1) {
            QString text = tr("Service exception, log upload failed, please try again!");
            dialog->setText(text);
        }
        auto wnd = window();
        dialog->move(wnd->geometry().topLeft());
        dialog->setFixedSize(wnd->size());
        dialog->show();
    }
    emit exitUploadLog();
}
