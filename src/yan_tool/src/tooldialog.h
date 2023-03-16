#ifndef RECOVERYDIALOG_H
#define RECOVERYDIALOG_H

#include <QDialog>

namespace Ui {
class ToolDialog;
}

class ToolDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ToolDialog(const QString& title, QWidget *parent = 0);
    ~ToolDialog();
    void setDisplayWidget(QWidget *displayWidget);

private slots:
    void on_closeBtn_clicked();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    Ui::ToolDialog *ui;
    bool leftBtnPressed_;
    QPoint lastPos_;
};

#endif // RECOVERYDIALOG_H
