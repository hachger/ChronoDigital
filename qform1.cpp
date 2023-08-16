#include "qform1.h"
#include "ui_qform1.h"

QForm1::QForm1(QWidget *parent)
    : QMainWindow(parent, Qt::FramelessWindowHint)
    , ui(new Ui::QForm1)
{
    ui->setupUi(this);

    this->setAttribute(Qt::WA_TranslucentBackground);

    QTimer1 = new QTimer(this);
    connect(QTimer1, &QTimer::timeout, this, &QForm1::OnQTimer1);

    ui->pushButton_5->setEnabled(false);

    timeCount = 0;

}

QForm1::~QForm1()
{
    delete ui;
}

void QForm1::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        lastPosX = event->pos().x();
        lastPosY = event->pos().y();
//        qDebug() << QString().number(lastPosX) + "," + QString().number(lastPosY);
        mouseIsPressed = true;
    }
}

void QForm1::mouseReleaseEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        mouseIsPressed = false;
//        qDebug() << "MOUSE RELEASED";
    }
}

void QForm1::mouseMoveEvent(QMouseEvent *event){
    if(mouseIsPressed){
        int newPosX = event->pos().x();
        int newPosY = event->pos().y();
        int dx = newPosX - lastPosX;
        int dy = newPosY - lastPosY;

        if(dx<10 && dx>-10)
            dx = 0;
        if(dy<10 && dy>-10)
            dy = 0;

        this->setGeometry(this->geometry().left()+dx, this->geometry().top()+dy, this->width(), this->height());
    }


}

void QForm1::OnQTimer1(){
    QString str;

    if(ui->pushButton_2->isChecked()){
        timeCountAux -= 20;
        if(timeCountAux == 0){
            QTimer1->stop();
            ui->pushButton_4->setChecked(false);
            ui->pushButton_5->setEnabled(false);
            ui->pushButton_3->setEnabled(true);
            if(!ui->pushButton_2->isChecked())
                ui->pushButton_2->setEnabled(true);
        }
    }
    else
        timeCountAux += 20;

    if(!ui->pushButton_5->isChecked()){
        str = QString("%1:").arg(timeCountAux/60000, 2, 10, QChar('0'));
        str = str + QString("%1:").arg((timeCountAux%60000)/1000, 2, 10, QChar('0'));
        str = str + QString("%1").arg((timeCountAux%1000)/10, 2, 10, QChar('0'));
        ui->label->setText(str);
    }
}

void QForm1::on_pushButton_clicked()
{
    close();
}


void QForm1::on_pushButton_2_clicked()
{
    bool ok;
    QString str;

    if(ui->pushButton_4->isChecked()){
        ui->pushButton_2->setChecked(true);
        return;
    }


    ui->lineEdit->setReadOnly(ui->pushButton_2->isChecked());
    if(ui->pushButton_2->isChecked()){
        ui->lineEdit->setReadOnly(true);


//        qDebug() << ui->lineEdit->text().trimmed();
        int pos = ui->lineEdit->text().indexOf(":");
//        qDebug() << QString().number(pos);
//        qDebug() << ui->lineEdit->text().mid(0, 2);
//        qDebug() << ui->lineEdit->text().mid(3, 2);

        timeCount = ui->lineEdit->text().mid(0, pos).toInt(&ok, 10)*60000;
        timeCount += (ui->lineEdit->text().mid(pos+1, ui->lineEdit->text().length()-pos).toInt(&ok, 10)*1000);

        str = QString("%1:").arg(timeCountAux/60000, 2, 10, QChar('0'));
        str = str + QString("%1").arg((timeCountAux%60000)/1000, 2, 10, QChar('0'));


//        qDebug() << QString().number(timeCount, 10);

    }
    else
        timeCount = 0;

    timeCountAux = timeCount;
    str = QString("%1:").arg(timeCountAux/60000, 2, 10, QChar('0'));
    str = str + QString("%1:").arg((timeCountAux%60000)/1000, 2, 10, QChar('0'));
    str = str + QString("%1").arg((timeCountAux%1000)/10, 2, 10, QChar('0'));
    ui->label->setText(str);
}


void QForm1::on_pushButton_4_clicked()
{
    QString str;

    if(ui->pushButton_4->isChecked()){
        str = QString("%1:").arg(timeCountAux/60000, 2, 10, QChar('0'));
        str = str + QString("%1:").arg((timeCountAux%60000)/1000, 2, 10, QChar('0'));
        str = str + QString("%1").arg((timeCountAux%1000)/10, 2, 10, QChar('0'));
        ui->label->setText(str);

        if(ui->pushButton_2->isChecked()){
            if(timeCountAux != 0)
                QTimer1->start(20);
        }
        else
            QTimer1->start(20);
    }
    else
        QTimer1->stop();

    ui->pushButton_4->setChecked(QTimer1->isActive());
    ui->pushButton_5->setChecked(false);
    ui->pushButton_5->setEnabled(QTimer1->isActive());
    ui->pushButton_3->setEnabled(!QTimer1->isActive());
    if(!ui->pushButton_2->isChecked())
        ui->pushButton_2->setEnabled(!QTimer1->isActive());

}


void QForm1::on_pushButton_3_clicked()
{
    QString str;

    timeCountAux = timeCount;
    str = QString("%1:").arg(timeCountAux/60000, 2, 10, QChar('0'));
    str = str + QString("%1:").arg((timeCountAux%60000)/1000, 2, 10, QChar('0'));
    str = str + QString("%1").arg((timeCountAux%1000)/10, 2, 10, QChar('0'));
    ui->label->setText(str);
}



