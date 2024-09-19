#include "Qt6WangYonglin/QThreader.h"

Qt6WangYonglin::QThreader::QThreader(QObject *parent)
    : QThread(parent),
    pauseFlag(false),
    stopFlag(false)
{

}

Qt6WangYonglin::QThreader::~QThreader()
{

}

Qt6WangYonglin::QThreader::State Qt6WangYonglin::QThreader::state() const
{
    State s = Stoped;
    if (!QThreader::isRunning())
    {
        s = Stoped;
    }
    else if (QThreader::isRunning() && pauseFlag)
    {
        s = Paused;
    }
    else if (QThreader::isRunning() && (!pauseFlag))
    {
        s = Running;
    }
    return s;
}

void Qt6WangYonglin::QThreader::startThread(QThreader::Priority pri)
{
    QThreader::start(pri);
}



void Qt6WangYonglin::QThreader::stopThread()
{
    if (QThreader::isRunning())
    {
        stopFlag = true;
        condition.wakeAll();
        QThreader::quit();
        QThreader::wait();
    }
}

void Qt6WangYonglin::QThreader::pauseThread()
{
    if (QThreader::isRunning())
    {
        pauseFlag = true;
    }
}

void Qt6WangYonglin::QThreader::resumeThread()
{
    if (QThreader::isRunning())
    {
        pauseFlag = false;
        condition.wakeAll();
    }
}

void Qt6WangYonglin::QThreader::run()
{
    //qDebug() << "enter QThreader : " << QThreader::currentQThreaderId();
    while (!stopFlag)
    {

        loopRunnable(); // do something...

        if (pauseFlag)
        {
            mutex.lock();
            condition.wait(&mutex);
            mutex.unlock();
        }
    }
    pauseFlag = false;
    stopFlag = false;

    //qDebug() << "exit QThreader : " << QThreader::currentQThreaderId();
}
