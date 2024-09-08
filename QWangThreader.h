#ifndef QTWANGTHREAD_H
#define QTWANGTHREAD_H

#include <QThread>
#include <QObject>
#include <QDebug>
#include <QMutex>
#include <QWaitCondition>
#include "QtWangYonglin_global.h"

class QTWANGYONGLIN_EXPORT QWangThreader: public QThread
{
    Q_OBJECT
public:
    explicit QWangThreader(QObject *parent = nullptr);
    ~QWangThreader() override;

    enum State
    {

        Stoped,     ///<停止状态，包括从未启动过和启动后被停止
        Running,    ///<运行状态
        Paused      ///<暂停状态
    };

    State state() const;


public slots:
    void loopStart(Priority pri = InheritPriority);
    void loopStop();
    void loopPause();
    void loopResume();
protected:
    virtual void run() override final;
    virtual void loopRunnable()=0;
private:
    std::atomic_bool pauseFlag;
    volatile std::atomic_bool stopFlag;
    QMutex mutex;
    QWaitCondition condition;
};
#endif // QTWANGTHREAD_H
