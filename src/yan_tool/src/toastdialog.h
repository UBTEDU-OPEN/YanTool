#ifndef TOASTDIALOG_H
#define TOASTDIALOG_H

#include <QDialog>

namespace Ui {
class ToastDialog;
}

class ToastDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ToastDialog(const QString& text, QWidget *parent = 0);
    ~ToastDialog();

private slots:
    void onTimeout();

private:
    Ui::ToastDialog *ui;
};

#endif // TOASTDIALOG_H
