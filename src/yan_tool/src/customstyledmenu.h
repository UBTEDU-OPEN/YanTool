#ifndef TIPDIALOG_H
#define TIPDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>

class  CustomStyledMenu : public QDialog
{
    Q_OBJECT

public:
    explicit CustomStyledMenu(QWidget *parent = nullptr);
    ~CustomStyledMenu();
    bool eventFilter(QObject *watched, QEvent *event) override;

    QPushButton *addMenuItem(QString text);

private:
    QVBoxLayout *contentLayout_;
};

#endif // TIPDIALOG_H
