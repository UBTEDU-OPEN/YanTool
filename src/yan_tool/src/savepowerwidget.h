#ifndef SAVEPOWERWIGET_H
#define SAVEPOWERWIGET_H

#include <QWidget>

namespace Ui {
class SavePowerWidget;
}

class SavePowerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SavePowerWidget(QWidget *parent = 0);
    ~SavePowerWidget();
    void setSaveMode(bool saveMode);

private slots:
    void on_switchBtn_clicked();

private:
    Ui::SavePowerWidget *ui;
    bool saveMode_;
};

#endif // SAVEPOWERWIGET_H
