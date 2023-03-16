#ifndef UPLOADLOGTHREAD_H
#define UPLOADLOGTHREAD_H

#include <QThread>

class UploadLogThread : public QThread
{
    Q_OBJECT

public:
    UploadLogThread(QObject* parent = nullptr);

signals:
    void uploadFinished(int);

protected:
    void run() override;
};

#endif // UPLOADLOGTHREAD_H
