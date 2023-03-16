#ifndef UPLOADLOGWIDGET_H
#define UPLOADLOGWIDGET_H

#include <QWidget>

#include "uploadlogthread.h"
#include "toastdialog.h"

namespace Ui {
class UploadLogWidget;
}

class UploadLogWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UploadLogWidget(QWidget *parent = 0);
    ~UploadLogWidget();

public slots:
    void onUploadResult(int result);

signals:
    void enterUploadLog();
    void exitUploadLog();

private slots:
    void on_pushButton_clicked();
    void onTextChanged();
    void onCheckStateChanged(int);

private:
    Ui::UploadLogWidget *ui;
    UploadLogThread *thread_;
};

#endif // UPLOADLOGWIDGET_H
