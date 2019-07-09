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
    connect(this->ui->c1Box,SIGNAL(currentIndexChanged(int)),this,SLOT(comValue()));
    connect(this->ui->c2Box,SIGNAL(currentIndexChanged(int)),this,SLOT(comValue()));
    connect(this->ui->c3Box,SIGNAL(currentIndexChanged(int)),this,SLOT(comValue()));
    connect(this->ui->testmodeCb,SIGNAL(clicked(bool)),this,SLOT(setTestMode(bool)));
    this->ui->label->setText("STATUS: Stop");
    this->ui->c1Box->setCurrentIndex(1);
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_startBtn_clicked()
{
    mSphinValue = this->ui->spinBox->value();
    mTimerThread.setValue(&mSphinValue);

    switch(this->ui->c4Box->currentText().toInt())
    {
        case 50 :
            mTimerThread.setTime(9500,9500);      // 50Hz
            break;
        case 100:
            mTimerThread.setTime(4600,4600);    //100Hz
            break;
        case 150:
            mTimerThread.setTime(2950,2950);    //150Hz
            break;
        case 500:
            mTimerThread.setTime(500,800);    //500Hz
            break;
        default:
            break;
    }

    mTimerThread.workStart();   //Start Thread
    mTimerThread.start();

    if(mSphinValue != 0)
    {
        this->ui->startBtn->setEnabled(false);
        this->ui->spinBox->setEnabled(false);
        this->ui->c1Box->setEnabled(false);
        this->ui->c2Box->setEnabled(false);
        this->ui->c3Box->setEnabled(false);
        this->ui->c4Box->setEnabled(false);
        this->ui->label->setText("STATUS: Running");
    }
}

void Dialog::on_exitBtn_clicked()
{
    if(mTimerThread.isRunning())
    {
        mTimerThread.workStop();    // Stop Thread
        mTimerThread.terminate();
        mTimerThread.wait();
    }

    this->close();
}

void Dialog::on_oneWorkStop()
{
    this->ui->startBtn->setEnabled(true);
    this->ui->spinBox->setEnabled(true);
    this->ui->c1Box->setEnabled(true);
    this->ui->c2Box->setEnabled(true);
    this->ui->c3Box->setEnabled(true);
    this->ui->c4Box->setEnabled(true);
    this->ui->label->setText("STATUS: Stop");
}

void Dialog::comValue()
{
    int a = this->ui->c1Box->currentText().toInt();
    int b = this->ui->c2Box->currentText().toInt();
    int c = this->ui->c3Box->currentText().toInt();
    int d = a * b * c;
    this->ui->spinBox->setValue(d);
}

void Dialog::setTestMode(bool value)
{
    if(value){
        mTimerThread.setMode(true);
        qDebug() << "true";
    }
    else{
        mTimerThread.setMode(false);
        qDebug() << "false";
    }
}
