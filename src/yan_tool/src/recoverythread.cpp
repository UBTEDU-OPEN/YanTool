#include "recoverythread.h"

#include "roshelper.h"

RecoveryThread::RecoveryThread(QObject* parent)
    : QThread(parent)
{

}

void RecoveryThread::run()
{
    int ret = RosHelper::getInstance()->lightRestoreSystem();
    emit lightRestoreFinished(ret);
}
