#ifndef WIDGET_H
#define WIDGET_H

#include <QtGui/QDialog>
#include <QtGui>
#include <QVector>
#include <QString>
#include <QFont>

#include <qextserialport.h>

#include <qwt_plot.h>
#include <qwt_plot_canvas.h>
#include <qwt_plot_curve.h>
#include <qwt_scale_draw.h>

#include "io.h"
#include "com.h"

//extern QextSerialPort *port;
//extern QString com;

namespace Ui {
class DIALOG;
}

class Widget : public QDialog
{
    Q_OBJECT


public:
    Widget(QWidget *parent = 0); //creation function
    ~Widget();//destructor

    void addpoint(int point);//add a new point to the graphe
    void upedge();
    void debugOutput(QtMsgType type, QString msg);





public slots:
    void receive(); //read data from the port
    void transmitCmd();
    void transmitCmd1();
    void my_timer_func();
    void my_compensate();
    void my_closetime();
    void my_slider();
    void button_callback();
    void button2_callback();

private :
    Ui::DIALOG *ui;

    void init_port();
    void init_plot();
    //void closeEvent(QCloseEvent *);


    QextSerialPort *port;
//    QwtPlot *plot, *plot1;
    QwtPlotCurve *curve, *curve1;
    QVector<double> *data_x, *data_y, *data_ysum;
//    QGridLayout *layout;
//    QPushButton *button, *button1, *button2;
//    QLineEdit *lineedit, *lineedit1;
//    QSlider *slider;
//    QLabel *label, *label1, *label2, *label3;
//    QLCDNumber *lcd, *lcd1;
//    QComboBox *combobox;

    int ysum, value, value1, p_count, mode;
    int compensate, close_time, slidev;
    bool restart, en_start;

    QString str0, str, str1, str2, str_close, str3, y, sum, str_start, str_stop, str_temp;

    QtMsgType type;
    QTime my_time, my_time1;
    QTimer *my_timer;




};

class RealScaleDraw: public QwtScaleDraw
{

public:

    RealScaleDraw(int p_count, int m) : form(p_count),mode(m)
    {
    }

    virtual QwtText label(double v) const
    {
        if (mode == 1) {
        //return QwtScaleDraw::label(v);
            QwtText ret_val = QwtText(QString::number((v+form*600)/20));  //sample rate 1/0.05s
            ret_val.setColor(Qt::blue);
            return ret_val;}
        else {
            QwtText ret_val = QwtText(QString::number(v));
            ret_val.setColor(Qt::blue);
            return ret_val;
        }
    }


private:

    int form, mode;
};


#endif // WIDGET_H
