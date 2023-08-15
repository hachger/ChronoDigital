#ifndef QFORM1_H
#define QFORM1_H

#include <QMainWindow>
#include <QTimer>

#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class QForm1; }
QT_END_NAMESPACE

class QForm1 : public QMainWindow
{
    Q_OBJECT

public:
    QForm1(QWidget *parent = nullptr);
    ~QForm1();

private slots:
    void OnQTimer1();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::QForm1 *ui;

    QTimer *QTimer1;

    int timeCount, timeCountAux;
};
#endif // QFORM1_H
