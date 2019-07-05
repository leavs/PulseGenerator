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
            b = QTime::currentTime().msec();
            writeFile("temp.txt","1");
            l = QTime::currentTime().msec();
            t = l - b;
            qDebug() << "write1 use " << t << "ms";
            msleep(1);
            b = QTime::currentTime().msec();
            writeFile("temp.txt","0");
            l = QTime::currentTime().msec();
            t = l - b;
            qDebug() << "write2 use " << t << "ms";
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
