#include "savepowerwidget.h"
#include "ui_savepowerwidget.h"

#include <QIcon>

#include "roshelper.h"

SavePowerWidget::SavePowerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SavePowerWidget)
{
    ui->setupUi(this);
}

SavePowerWidget::~SavePowerWidget()
{
    delete ui;
}

void SavePowerWidget::setSaveMode(bool saveMode)
{
    saveMode_ = saveMode;
    if(saveMode_) {
        ui->switchState->setText(tr("ON"));
        ui->switchBtn->setChecked(true);
    } else {
        ui->switchState->setText(tr("OFF"));
        ui->switchBtn->setChecked(false);
    }
}

void SavePowerWidget::on_switchBtn_clicked()
{
    setSaveMode(!saveMode_);
    RosHelper::getInstance()->setEnergyModeEnable(saveMode_);
}
