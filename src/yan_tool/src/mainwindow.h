#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

namespace Ui {
class MainWindow;
}


class MainWidget;
class RecoveryWidget;
class SavePowerWidget;
class UploadLogWidget;

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

public slots:
    void handleMessage(const QString &);
    void onEnterRestore();
    void onExitRestore();
    void onEnterUploadLog();
    void onExitUploadLog();

protected:
  void mousePressEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);
  void resizeEvent(QResizeEvent *event);

private slots:
  void onBackBtnClicked();
  void on_minBtn_clicked();
  void on_closeBtn_clicked();
  void onRecoveryClicked();
  void onSavePowerClicked();
  void onUploadLogClicked();

private:
  Ui::MainWindow *ui;
  bool leftBtnPressed_;
  QPoint pressedPos_;
  MainWidget *mainWidget_;
  RecoveryWidget *recoveryWidget_;
  SavePowerWidget *savePowerWidget_;
  UploadLogWidget *uploadLogWidget_;
  bool restoring_;
  bool uploadingLog_;
  QPushButton *backBtn_;
};

#endif // MAINWINDOW_H
