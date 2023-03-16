#include "uploadlogthread.h"

#include "roshelper.h"

UploadLogThread::UploadLogThread(QObject* parent)
    : QThread(parent)
{

}

void UploadLogThread::run()
{
    std::string data = "upload";
    int updateResult = RosHelper::getInstance()->uploadLog(data);
    emit uploadFinished(updateResult);
}
