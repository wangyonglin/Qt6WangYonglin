#include "QWangThreader.h"

QWangThreader::QWangThreader(QObject *parent)
    : QThread(parent),
    pauseFlag(false),
    stopFlag(false)
{}

QWangThreader::~QWangThreader()
{

}

QWangThreader::State QWangThreader::state() const
{
    State s = Stoped;
    if (!QThread::isRunning())
    {
        s = Stoped;
    }
    else if (QThread::isRunning() && pauseFlag)
    {
        s = Paused;
    }
    else if (QThread::isRunning() && (!pauseFlag))
    {
        s = Running;
    }
    return s;
}

void QWangThreader::loopStart(QThread::Priority pri)
{
    QThread::start(pri);
}



void QWangThreader::loopStop()
{
    if (QThread::isRunning())
    {
        stopFlag = true;
        condition.wakeAll();
        QThread::quit();
        QThread::wait();
    }
}

void QWangThreader::loopPause()
{
    if (QThread::isRunning())
    {
        pauseFlag = true;
    }
}

void QWangThreader::loopResume()
{
    if (QThread::isRunning())
    {
        pauseFlag = false;
        condition.wakeAll();
    }
}

void QWangThreader::run()
{
    //qDebug() << "enter thread : " << QThread::currentThreadId();
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

    //qDebug() << "exit thread : " << QThread::currentThreadId();
}
