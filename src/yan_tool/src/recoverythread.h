#ifndef RECOVERYTHREAD_H
#define RECOVERYTHREAD_H

#include <QThread>

class RecoveryThread : public QThread
{
    Q_OBJECT
public:
    RecoveryThread(QObject* parent = nullptr);

signals:
    void lightRestoreFinished(int);

protected:
    void run() override;
};

#endif // RECOVERYTHREAD_H
