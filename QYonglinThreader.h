#ifndef QTWANGTHREAD_H
#define QTWANGTHREAD_H

#include <QThread>
#include <QObject>
#include <QDebug>
#include <QMutex>
#include <QWaitCondition>
#include "QtWangYonglin_global.h"

namespace  Qt6WangYonglin {


class QTWANGYONGLIN_EXPORT QYonglinThreader: public QThread
{
    Q_OBJECT
public:
    explicit QYonglinThreader(QObject *parent = nullptr);
    ~QYonglinThreader() override;

    enum State
    {

        Stoped,     ///<停止状态，包括从未启动过和启动后被停止
        Running,    ///<运行状态
        Paused      ///<暂停状态
    };

    State state() const;


public slots:
    void startThread(Priority pri = InheritPriority);
    void stopThread();
    void pauseThread();
    void resumeThread();
protected:
    virtual void run() override final;
    virtual void loopRunnable()=0;
private:
    std::atomic_bool pauseFlag;
    volatile std::atomic_bool stopFlag;
    QMutex mutex;
    QWaitCondition condition;
};
}
#endif // QTWANGTHREAD_H
