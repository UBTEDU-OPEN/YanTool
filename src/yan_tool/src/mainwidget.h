#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>

class RosHelper;

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

signals:
    void restoreClicked();
    void saveEnergyClicked();
    void uploadLogClicked();

private:
  void updateRomVersion();
  void updateAvailableSpace();
  void updateUserDataSize();
  void getDeviceInfo();

private:
    Ui::MainWidget *ui;
    QMovie *movie_;
    QTimer *timer_;
    RosHelper *inst_;
};

#endif // MAINWIDGET_H
