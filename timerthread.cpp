#include "timerthread.h"
#include <QFile>
#include <QIODevice>
#include <QDebug>
#include <QTime>

TimerThread::TimerThread()
{
}

void TimerThread::run()
{
    while(!mStop)
    {
        while(mSphinxValue > 0)
        {
            writeFile("/dev/chipsee-gpio1","1");
            usleep(mHtime);
            writeFile("/dev/chipsee-gpio1","0");
            usleep(mLtime);

            if(!testmode)
            {
                mSphinxValue--;
                if(mSphinxValue == 0)
                    emit oneWorkStop();
            }
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

void TimerThread::setMode(bool value)
{
    testmode = value;
}

void TimerThread::setTime(int htime, int ltime)
{
    mHtime = htime;
    mLtime = ltime;
}

bool TimerThread::writeFile(const QString &filename, QString value)
{
    QFile mFile(filename);
    if(!mFile.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;
    QTextStream mTextStream(&mFile);
    mTextStream << value;
    mFile.close();
    return true;
}
