#ifndef NOTICEDIALOG_H
#define NOTICEDIALOG_H

#include <QDialog>

namespace Ui {
class NoticeDialog;
}

class NoticeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NoticeDialog(QWidget *parent = 0);
    ~NoticeDialog();
    void setText(const QString& text);

private slots:
    void on_ok_clicked();

private:
    Ui::NoticeDialog *ui;
};

#endif // NOTICEDIALOG_H
