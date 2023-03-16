#ifndef RECOVERYWIDGET_H
#define RECOVERYWIDGET_H

#include <QWidget>
#include "toastdialog.h"
#include "recoverythread.h"

namespace Ui {
class RecoveryWidget;
}

class RecoveryWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RecoveryWidget(QWidget *parent = 0);
    ~RecoveryWidget();

public slots:
    void onRestoreFinished(int result);

signals:
    void enterRestore();
    void exitRestore();

private slots:
    void on_pushButton_clicked();

private:
    Ui::RecoveryWidget *ui;
    RecoveryThread *thread_;
};

#endif // RECOVERYWIDGET_H
