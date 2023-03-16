#include "mainwidget.h"
#include "ui_mainwidget.h"

#include <QTimer>
#include <QMovie>

#include "roshelper.h"
#include "custombutton.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget),
    movie_(nullptr),
    timer_(nullptr)
{
    ui->setupUi(this);

    ui->versionInfo->setTextInteractionFlags(Qt::TextSelectableByMouse);

    ui->restoreBtn->setBgUrl(":/res/img_recovery_1.png",":/res/img_recovery_1_p.png");
    ui->restoreBtn->setText(tr("Lightweight recovery"));
    ui->saveEnergyBtn->setBgUrl(":/res/img_energy_save_mode_1.png",":/res/img_energy_save_mode_1_p.png");
    ui->saveEnergyBtn->setText(tr("Energy-saving mode"));
    ui->uploadLogBtn->setBgUrl(":/res/img_user_date.png",":/res/img_user_date_P.png");
    ui->uploadLogBtn->setText(tr("Log upload"));

    connect(ui->restoreBtn,&CustomButton::btnClicked,this,&MainWidget::restoreClicked);
    connect(ui->saveEnergyBtn,&CustomButton::btnClicked,this,&MainWidget::saveEnergyClicked);
    connect(ui->uploadLogBtn,&CustomButton::btnClicked,this,&MainWidget::uploadLogClicked);

    inst_ = RosHelper::getInstance();

    timer_ = new QTimer(this);
    connect(timer_,&QTimer::timeout,this,&MainWidget::getDeviceInfo);
    timer_->start(5000);

    movie_ = new QMovie(this);
    movie_->setFileName(":/res/loading.gif");
    movie_->setScaledSize(QSize(28,28));
    movie_->start();
    ui->versionInfo->setMovie(movie_);
    ui->userDataSize->setMovie(movie_);
    ui->availableSpace->setMovie(movie_);

    getDeviceInfo();
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::updateRomVersion()
{
    QString versionInfo = tr("Robot frameware-%1\nPC Blockly-%2\nSN-%3").arg(QString::fromStdString(inst_->framewareVer_)).arg(QString::fromStdString(inst_->blocklyVer_)).arg(QString::fromStdString(inst_->sn_));
    ui->versionInfo->setText(versionInfo);
}

void MainWidget::updateAvailableSpace()
{
    ui->availableSpace->setText(QString("%1MB").arg(inst_->availableSpace_));
}

void MainWidget::updateUserDataSize()
{
    ui->userDataSize->setText(QString("%1MB").arg(inst_->userDataSize_));
}

void MainWidget::getDeviceInfo()
{
    inst_->getFramewareVersion();
    inst_->getBlocklyVersion();
    inst_->getSn();
    inst_->getAvailableSpace();
    inst_->getUserDataSize();

    if(!inst_->framewareVer_.empty() &&
            !inst_->blocklyVer_.empty() &&
            !inst_->sn_.empty() &&
            inst_->availableSpace_ != INVALID_SIZE &&
            inst_->userDataSize_ != INVALID_SIZE &&
            movie_ != nullptr) {
        movie_->stop();
        movie_->deleteLater();
        movie_ = nullptr;
    }

    if(!inst_->framewareVer_.empty() &&
            !inst_->blocklyVer_.empty() &&
            !inst_->sn_.empty()){
        updateRomVersion();
    }

    if(inst_->availableSpace_ != INVALID_SIZE) {
        updateAvailableSpace();
    }

    if(inst_->userDataSize_ != INVALID_SIZE) {
        updateUserDataSize();
    }
}
