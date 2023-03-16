#ifndef ICONTOASTDIALOG_H
#define ICONTOASTDIALOG_H

#include <QDialog>

namespace Ui {
class IconToastDialog;
}

class IconToastDialog : public QDialog
{
    Q_OBJECT

public:
    explicit IconToastDialog(QString text, QWidget *parent = 0);
    ~IconToastDialog();

private slots:
    void onTimeout();

private:
    Ui::IconToastDialog *ui;
};

#endif // ICONTOASTDIALOG_H
