#ifndef COM_H
#define COM_H


#include <QDialog>
#include <QtGui>
#include <QtGui/QWidget>
#include "io.h"
#include "dialog.h"

//extern QextSerialPort *port;
//extern QString com;

namespace Ui {
class COM;
}


class COM : public QDialog
{
    Q_OBJECT


public:
    explicit COM(QWidget *parent = 0);
    ~COM();

public slots:
    void button_callback();
    void show_widget();

    //void init_port();
    //QextSerialPort *port;

private:
    Ui::COM *ui;
    //Widget *w;

};

#endif // COM_H
