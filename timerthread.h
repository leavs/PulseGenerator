#ifndef TIMERTHREAD_H
#define TIMERTHREAD_H

#include <QThread>

class TimerThread : public QThread
{
    Q_OBJECT

private:
    bool mStop = true;
    int mSphinxValue = 0;
    int b,l,t;

protected:
    void run() Q_DECL_OVERRIDE;

public:
    TimerThread();
    void workStart();
    void workStop();
    void setValue(int*);
    bool writeFile(const QString &filename, QString value);

signals:
    void oneWorkStop();

};

#endif // TIMERTHREAD_H
