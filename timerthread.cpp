#include "timerthread.h"
#include <QDebug>

TimerThread::TimerThread()
{

}

void TimerThread::run()
{
    while(!mStop)
    {
        while(mSphinxValue > 0)
        {
            qDebug() << "HIGH";
            msleep(1);
            qDebug() << "LOW";
            msleep(1);
            mSphinxValue--;
            if(mSphinxValue == 0)
                emit oneWorkStop();
        }
        msleep(500);
    }
    quit();
    qDebug() <<"Thread Quit";
}

void TimerThread::workStart()
{
    mStop = false;
}

void TimerThread::workStop()
{
    mStop = true;
}

void TimerThread::setValue(int *value)
{
    mSphinxValue = *value;
}
