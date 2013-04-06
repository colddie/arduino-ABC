#ifndef IO_H
#define IO_H

#include "dialog.h"
#include "com.h"

class io
{

public:
      io();
      //void write_to_file(QString str, QString sum);
      void write_to_file(QString y, QString sum, QVector <double> *data_ysum);

};


#endif // IO_H
