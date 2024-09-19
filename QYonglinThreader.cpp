#include "QYonglinThreader.h"

Qt6WangYonglin::QYonglinThreader::QYonglinThreader(QObject *parent)
    : QThread(parent),
    pauseFlag(false),
    stopFlag(false)
{

}

Qt6WangYonglin::QYonglinThreader::~QYonglinThreader()
{

}

Qt6WangYonglin::QYonglinThreader::State Qt6WangYonglin::QYonglinThreader::state() const
{
    State s = Stoped;
    if (!QYonglinThreader::isRunning())
    {
        s = Stoped;
    }
    else if (QYonglinThreader::isRunning() && pauseFlag)
    {
        s = Paused;
    }
    else if (QYonglinThreader::isRunning() && (!pauseFlag))
    {
        s = Running;
    }
    return s;
}

void Qt6WangYonglin::QYonglinThreader::startThread(QYonglinThreader::Priority pri)
{
    QYonglinThreader::start(pri);
}



void Qt6WangYonglin::QYonglinThreader::stopThread()
{
    if (QYonglinThreader::isRunning())
    {
        stopFlag = true;
        condition.wakeAll();
        QYonglinThreader::quit();
        QYonglinThreader::wait();
    }
}

void Qt6WangYonglin::QYonglinThreader::pauseThread()
{
    if (QYonglinThreader::isRunning())
    {
        pauseFlag = true;
    }
}

void Qt6WangYonglin::QYonglinThreader::resumeThread()
{
    if (QYonglinThreader::isRunning())
    {
        pauseFlag = false;
        condition.wakeAll();
    }
}

void Qt6WangYonglin::QYonglinThreader::run()
{
    //qDebug() << "enter QYonglinThreader : " << QYonglinThreader::currentQYonglinThreaderId();
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

    //qDebug() << "exit QYonglinThreader : " << QYonglinThreader::currentQYonglinThreaderId();
}
