#include "dialog.h"
#include "ui_dialog.h"
#include "timerthread.h"
#include <QDebug>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    connect(&mTimerThread,SIGNAL(oneWorkStop()),this,SLOT(on_oneWorkStop()));
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_startBtn_clicked()
{
    mSphinValue = this->ui->spinBox->value();
    qDebug() << "mSphinxValue = " << mSphinValue;
    mTimerThread.setValue(&mSphinValue);
    mTimerThread.workStart();   //Start Thread
    mTimerThread.start();

    this->ui->startBtn->setEnabled(false);
    this->ui->spinBox->setEnabled(false);
}

void Dialog::on_exitBtn_clicked()
{
    if(mTimerThread.isRunning())
    {
        mTimerThread.workStop();    // Stop Thread
        mTimerThread.wait();
    }

    this->close();
}

void Dialog::on_oneWorkStop()
{
    this->ui->startBtn->setEnabled(true);
    this->ui->spinBox->setEnabled(true);
}
