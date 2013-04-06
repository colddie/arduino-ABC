#include <QtGui/QApplication>
#include "dialog.h"
#include "io.h"
#include "com.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // debugfile predix
    QDateTime sometime = QDateTime::currentDateTime();
    QString timestring = sometime.toString("yyyyMMdd_hhmmss");
    //QString my_filename(timestring + QString("debugfile") + QString(".txt"));

    QDir my_dir("data");
    my_dir.mkdir(timestring);

    QFile debugfile("data/"+timestring+"/debug.txt");
    debugfile.open(QIODevice::WriteOnly | QIODevice::Text);
    debugfile.flush();
    debugfile.close();

    //global variables
    QString com;
    bool ind_close = 0;
    a.setProperty("my_global_string", com); //current selected COM
    a.setProperty("my_global_prefix", timestring);
    a.setProperty("my_close_dialog", ind_close); // initialize COM signal not to close main dialog

    //
    COM c;
    c.show();

    return a.exec();
}
