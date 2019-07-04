#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <timerthread.h>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT
private:
    TimerThread mTimerThread;
    int mSphinValue = 0;
public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_startBtn_clicked();
    void on_exitBtn_clicked();
    void on_oneWorkStop();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
