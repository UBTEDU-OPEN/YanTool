#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGuiApplication>
#include <QMouseEvent>
#include <QResizeEvent>
#include <QScreen>

#include "tooldialog.h"
#include "recoverywidget.h"
#include "savepowerwidget.h"
#include "uploadlogwidget.h"
#include "mainwidget.h"
#include "roshelper.h"


enum kStackWidgetIndex {
    kMainWidgetIndex = 0,
    kRecoveryWidgetIndex,
    kSavePowerWidgetIndex,
    kUploadLogWidgetIndex
};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    leftBtnPressed_(false),
    restoring_(false),
    uploadingLog_(false)
{
    ui->setupUi(this);
    backBtn_ = new QPushButton(this);
    backBtn_->setObjectName("backBtn");
    backBtn_->setStyleSheet("QPushButton#backBtn { border-image: url(:/res/ic_back.png); }"
                            "QPushButton#backBtn:pressed { border-image: url(:/res/ic_back_p.png); }");
    backBtn_->setFixedSize(QSize(36,36));
    backBtn_->setIconSize(QSize(36,36));

    backBtn_->move(20,20);

    connect(backBtn_,&QPushButton::clicked,this,&MainWindow::onBackBtnClicked);

    auto flags = windowFlags();
    setWindowFlags(flags | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    mainWidget_ = new MainWidget(ui->stackedWidget);
    connect(mainWidget_,&MainWidget::restoreClicked,this,&MainWindow::onRecoveryClicked);
    connect(mainWidget_,&MainWidget::saveEnergyClicked,this,&MainWindow::onSavePowerClicked);
    connect(mainWidget_,&MainWidget::uploadLogClicked,this,&MainWindow::onUploadLogClicked);
    ui->stackedWidget->addWidget(mainWidget_);
    recoveryWidget_ = new RecoveryWidget(ui->stackedWidget);
    ui->stackedWidget->addWidget(recoveryWidget_);
    savePowerWidget_ = new SavePowerWidget(ui->stackedWidget);
    ui->stackedWidget->addWidget(savePowerWidget_);
    uploadLogWidget_ = new UploadLogWidget(ui->stackedWidget);
    ui->stackedWidget->addWidget(uploadLogWidget_);

    connect(recoveryWidget_,&RecoveryWidget::enterRestore,this,&MainWindow::onEnterRestore);
    connect(recoveryWidget_,&RecoveryWidget::exitRestore,this,&MainWindow::onExitRestore);
    connect(uploadLogWidget_,&UploadLogWidget::enterUploadLog,this,&MainWindow::onEnterUploadLog);
    connect(uploadLogWidget_,&UploadLogWidget::exitUploadLog,this,&MainWindow::onExitUploadLog);

    backBtn_->setEnabled(false);
    backBtn_->setVisible(false);
    ui->stackedWidget->setCurrentIndex(kMainWidgetIndex);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    auto pos = event->pos();
    if(event->button() == Qt::LeftButton /*&& ui->titleWidget->geometry().contains(pos)*/) {
        leftBtnPressed_ = true;
        pressedPos_ = pos;
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(leftBtnPressed_) {
        QPoint position = event->globalPos() - pressedPos_;
        move(position);
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(leftBtnPressed_) {
        leftBtnPressed_ = false;
    }
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    auto screen = QGuiApplication::primaryScreen();
    auto screenRect = screen->geometry();
    auto wndSize = event->size();
    move((screenRect.width()-wndSize.width())/2,(screenRect.height()-wndSize.height())/2);
}

void MainWindow::onBackBtnClicked()
{
    if(restoring_) {
        auto dialog = new ToastDialog(tr("System restore underway, complete soon!"),this);
        auto wnd = window();
        auto pos = wnd->geometry().topLeft();
        auto wndSize = wnd->size();
        pos.setX(pos.x() + (wndSize.width()-dialog->width())/2);
        pos.setY(pos.y() + (wndSize.height()-dialog->height())/2);
        dialog->move(pos);
        dialog->show();
    } else if(uploadingLog_) {
        auto dialog = new ToastDialog(tr("Log upload underway, complete soon!"),this);
        auto wnd = window();
        auto pos = wnd->geometry().topLeft();
        auto wndSize = wnd->size();
        pos.setX(pos.x() + (wndSize.width()-dialog->width())/2);
        pos.setY(pos.y() + (wndSize.height()-dialog->height())/2);
        dialog->move(pos);
        dialog->show();
    } else {
        backBtn_->setEnabled(false);
        backBtn_->setVisible(false);
        ui->banner->setPixmap(QPixmap(":/res/img_banner_home.png"));
        ui->banner->setFixedHeight(210);
        ui->stackedWidget->setCurrentIndex(kMainWidgetIndex);
    }
}

void MainWindow::on_minBtn_clicked()
{
    showMinimized();
}

void MainWindow::on_closeBtn_clicked()
{
    if(restoring_) {
        auto dialog = new ToastDialog(tr("System restore underway, complete soon!"),this);
        auto wnd = window();
        auto pos = wnd->geometry().topLeft();
        auto wndSize = wnd->size();
        pos.setX(pos.x() + (wndSize.width()-dialog->width())/2);
        pos.setY(pos.y() + (wndSize.height()-dialog->height())/2);
        dialog->move(pos);
        dialog->show();
    } else if(uploadingLog_) {
        auto dialog = new ToastDialog(tr("Log upload underway, complete soon!"),this);
        auto wnd = window();
        auto pos = wnd->geometry().topLeft();
        auto wndSize = wnd->size();
        pos.setX(pos.x() + (wndSize.width()-dialog->width())/2);
        pos.setY(pos.y() + (wndSize.height()-dialog->height())/2);
        dialog->move(pos);
        dialog->show();
    } else {
        close();
    }
}

void MainWindow::onRecoveryClicked()
{
    backBtn_->setEnabled(true);
    backBtn_->setVisible(true);
    ui->banner->setText(tr("Lightweight recovery"));
    ui->banner->setFixedHeight(60);
    ui->stackedWidget->setCurrentIndex(kRecoveryWidgetIndex);
}

void MainWindow::onSavePowerClicked()
{
    bool saveMode = true;
    RosHelper::getInstance()->getEnergyModeEnabled(saveMode);
    savePowerWidget_->setSaveMode(saveMode);
    backBtn_->setEnabled(true);
    backBtn_->setVisible(true);
    ui->banner->setText(tr("Energy-saving mode"));
    ui->banner->setFixedHeight(60);
    ui->stackedWidget->setCurrentIndex(kSavePowerWidgetIndex);
}

void MainWindow::onUploadLogClicked()
{
    backBtn_->setEnabled(true);
    backBtn_->setVisible(true);
    ui->banner->setText(tr("Log upload"));
    ui->banner->setFixedHeight(60);
    ui->stackedWidget->setCurrentIndex(kUploadLogWidgetIndex);
}

void MainWindow::handleMessage(const QString &)
{
    showNormal();
}

void MainWindow::onEnterRestore()
{
    restoring_ = true;
}

void MainWindow::onExitRestore()
{
    restoring_ = false;
}

void MainWindow::onEnterUploadLog()
{
    uploadingLog_ = true;
}

void MainWindow::onExitUploadLog()
{
    uploadingLog_ = false;
}
