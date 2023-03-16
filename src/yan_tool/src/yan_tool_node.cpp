#include <ros/ros.h>
#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <QDebug>

#include "mainwindow.h"
#include "roshelper.h"
#include <QtSingleApplication>

int main(int argc, char **argv)
{
    QtSingleApplication a(argc, argv);
    if(a.isRunning())
    {
        a.sendMessage("process is already in running");
        return EXIT_SUCCESS;
    }

#ifndef NO_ROS_FLAG
  ros::init(argc, argv, "yan_tool_node");
  ros::AsyncSpinner spinner(1);
#endif

  auto inst = RosHelper::getInstance();
  inst->rosInit();
#ifndef NO_ROS_FLAG
  spinner.start();
#endif

  QLocale locale;
  QTranslator translator;
  QTranslator qtbaseTrans;
  if(locale.language() == QLocale::Chinese) {
      translator.load(":/yantool.qm");
      a.installTranslator(&translator);
      qtbaseTrans.load(":/qtbase_zh_CN.qm");
      a.installTranslator(&qtbaseTrans);
  }

  a.setStyleSheet("QWidget:focus{outline:none;}" \
                  "QMenu::item:selected{background-color: #EEF5FA; color: black;}"); //

  MainWindow w;
  w.show();

  a.setActivationWindow(&w);
  QObject::connect(&a, &QtSingleApplication::messageReceived, &w, &MainWindow::handleMessage);

  return a.exec();

}
