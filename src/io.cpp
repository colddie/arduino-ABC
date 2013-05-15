#include <iostream>
#include <fstream>
#include <sstream>
#include <QDateTime>

#include "io.h"

using namespace std;

io::io()

{

}

// write when destruction
void io::write_to_file(QString y, QString sum, QVector <double> *data_ysum)
{

    if (qApp->property("my_close_dialog") == 0) {
//QDateTime sometime = QDateTime::currentDateTime();
//QString timestring = sometime.toString("yyyyMMdd_hhmmss");
//QString my_filename1(timestring + QString("data") + QString(".txt"));

QString timestring = qApp->property("my_global_prefix").toString();
QFile my_file1("data/"+timestring+"/volume.txt");
my_file1.open(QIODevice::WriteOnly | QIODevice::Text);
QFile my_file2("data/"+timestring+"/flow.txt");
my_file2.open(QIODevice::WriteOnly | QIODevice::Text);

QTextStream out1(&my_file1);
out1 << sum;
my_file1.close();
QTextStream out2(&my_file2);
out2 << y;
my_file2.close();
    }

}


//void io::write_to_file(QString str, QString sum)
//{

//    QString my_filename(timestring + QString("file") + QString(".txt"));
//    QFile my_file(my_filename);
//    my_file.open(QIODevice::ReadWrite | QIODevice::Text);

//    QTextStream out(&my_file);
//    out << str;
//    my_file.close();
    //return;

//    QString my_filename1(timestring + QString("data") + QString(".txt"));
//    QFile my_file1(my_filename1);
//    my_file1.open(QIODevice::WriteOnly | QIODevice::Text);

//    QTextStream out1(&my_file1);
//    out1 << sum;
//    my_file1.close();
    //return;

//    QFile my_file1("my_data.txt");
//    my_file1.open(QIODevice::WriteOnly | QIODevice::Text);

//    QDataStream out1(&my_file1);
//    double *data = data_ysum.data();
//    for (int i=0; i<(data_ysum.size()); i++) {
//        //data[i] = &data_ysum;
//        out1.setByteOrder(QDataStream::LittleEndian); // set little endian byte order
//        out1 << data[i] << "\n";
//    }

//    my_file1.close();

//}
