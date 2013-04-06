#include "dialog.h"




Widget::Widget(QWidget *parent)
    : QDialog(parent)

{


    //creation of tables of your data
    data_x = new QVector<double>;
    data_y = new QVector<double>;
    data_ysum = new QVector<double>;
    ysum = 0;
    p_count = 0; //first 30s
    restart = 0;
    en_start = 0;

    //initiation of the graphic
    init_plot();



    //
    button = new QPushButton (this);
    button->setText("Start");
    button->setMinimumSize(60, 80);
    button->setFont(QFont ("AnyStyle", 16));

    button1 = new QPushButton(this);
    button1->setText("Close");
    button1->setMinimumSize(60, 80);
    button1->setFont(QFont ("AnyStyle", 16));
    button1->setDisabled(1);

    button2 = new QPushButton(this);
    button2->setText("Stop");
    button2->setMinimumSize(60, 80);
    button2->setFont(QFont ("AnyStyle", 16));
    button2->setDisabled(1);

    //button2 = new QPushButton(this);
    //button2->setText("open");
    //button2->setMaximumSize(100, 40);

    //
    lineedit = new QLineEdit(this);
    lineedit->setText("0");
    lineedit->setFixedSize(30,20);
    lineedit->setAlignment(Qt::AlignCenter);

    lineedit1 = new QLineEdit(this);
    lineedit1->setText("6");
    lineedit1->setFixedSize(30,20);
    lineedit1->setAlignment(Qt::AlignCenter);

    slider = new QSlider(this);
    slider->setOrientation(Qt::Horizontal);
    slider->setFixedSize(100,20);
    slider->setMinimum(0);
    slider->setMaximum(9);
    slider->setValue(5);


    //
    label = new QLabel(this);
    label->setText("<font size=10>Status open</font>");

    label1 = new QLabel(this);
    label1->setText("<font size=5>Offset</font>");
    label1->setGeometry(QRect(50,80,60,20));

    label2 = new QLabel(this);
    label2->setText("<font size=3>s</font>");
    label2->setGeometry(QRect(180,550,20,20));

    label3 = new QLabel(this);
    label3->setText("<font size=3>senstivity</font>");
    //label3->setGeometry(QRect(180,550,20,20));

    //time display
    lcd = new QLCDNumber(this);
    lcd->setSegmentStyle(QLCDNumber::Flat);
    lcd->setFixedSize(180,100);

    lcd->setAutoFillBackground(true);// see the different if you comment that line out.
    QPalette Pal = lcd->palette();
    Pal.setColor(QPalette::Normal, QPalette::WindowText, Qt::red);
    //Pal.setColor(QPalette::Normal, QPalette::Window, Qt::black);
    lcd->setPalette(Pal);



    lcd1 = new QLCDNumber(this);
    lcd1->setSegmentStyle(QLCDNumber::Flat);
    lcd1->setFixedSize(180,100);

    //creation of a layout to put the graphic inside
    layout = new QGridLayout( this );
    layout->setContentsMargins( 5, 5, 5, 5 ); //we set the margin of the layout
    layout->addWidget(plot, 0, 1); //we add the plot
    layout->addWidget(plot1, 1, 1);
    layout->addWidget(button, 1, 0, Qt::AlignTop);
    layout->addWidget(button1, 2, 0, Qt::AlignTop);
    layout->addWidget(button2, 2, 1, Qt::AlignRight);
    //layout->addWidget(combobox, 0, 0, Qt::AlignTop);
    layout->addWidget(lineedit, 0, 0, Qt::AlignCenter | Qt::AlignTop);
    layout->addWidget(slider, 0, 0, Qt::AlignRight);
    layout->addWidget(lineedit1, 2, 1, Qt::AlignCenter | Qt::AlignLeft);
    layout->addWidget(label, 3, 0, Qt::AlignCenter);
    layout->addWidget(label1, 0, 0, Qt::AlignTop |Qt::AlignLeft);
    layout->addWidget(label3, 0, 0, Qt::AlignLeft);
    layout->addWidget(lcd, 3, 1, Qt::AlignLeft);
    layout->addWidget(lcd1, 3, 1, Qt::AlignRight);



    my_timer = new QTimer(this);

    connect(my_timer, SIGNAL(timeout()), this, SLOT(my_timer_func()));


    //connection between the slider event and the transmission function
    connect(button, SIGNAL(clicked()), this, SLOT(button_callback()));
    connect(button1, SIGNAL(clicked()), this, SLOT(transmitCmd()));
    connect(button2, SIGNAL(clicked()), this, SLOT(button2_callback()));
    //connect(button2, SIGNAL(clicked()), this, SLOT(transmitCmd1()));

    //connection between the slider event and the lcd value
    //connect(button1, SIGNAL(clicked()), this, SLOT(lcddisplay()));


    connect(lineedit, SIGNAL(editingFinished()), this, SLOT(my_compensate()));
    connect(lineedit1, SIGNAL(editingFinished()), this, SLOT(my_closetime()));

    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(my_slider()));
    //initiation of the port com
    init_port();


    //connection betweent the reception of a data and the function receive
    connect(port, SIGNAL(readyRead()), this, SLOT(receive()));
}

Widget::~Widget()
{
    port->close();
    QTextStream out(stdout);
    QString temp;
    temp = QString::number(my_time1.elapsed()/1000.000, 'f', 3);
    str3 = QString(temp + "s" + " " + QString("port closed"));
    //out << str3 << endl;
    debugOutput(QtDebugMsg, str3);

    //write to file after destruction
    io my_io;
//    str0 = QString(str+QString("\n")+str_start+QString("\n")+str_close+QString("\n")+str_stop+QString("\n")+str3);
    my_io.write_to_file(y, sum, data_ysum);


}


void Widget::init_port()
{

    QTextStream out(stdout);//creation of a stream belonging to the console (you have to activate the console in the .pro file to display it)


    //QString portname = "COM3";
    QString portname = qApp->property("my_global_string").toString(); //get current selected COM
    port = new QextSerialPort(portname, QextSerialPort::EventDriven); //we create the port

    port->open(QIODevice::ReadWrite | QIODevice::Unbuffered); //we open the port

    if(!port->isOpen())
    {

        QMessageBox::StandardButton reply;
        reply = QMessageBox::warning(this, "port error",
                                     "Impossible to open the port " +portname +"!",
                                     QMessageBox::Yes);

//        if (reply == QMessageBox::Yes)
//        {
//        this->deleteLater();
//        }

        qApp->setProperty("my_close_dialog", 1); // set COM signal to close main dialog


    }


    //we set the port properties
    port->setBaudRate(BAUD9600);//modify the port settings on your own
    port->setFlowControl(FLOW_OFF);
    port->setParity(PAR_NONE);
    port->setDataBits(DATA_8);
    port->setStopBits(STOP_1);

    str = "port open";
    //out << str << endl; // we write on the console
    debugOutput(QtDebugMsg, str);


}


//void Widget::closeEvent(QCloseEvent *event)
//{

//     event->accept();

//}


void Widget::init_plot()
{

    plot = new QwtPlot(this); //creation of the plot
    QPalette Pal = plot->palette();
    //Pal.setColor(QPalette::Normal, QPalette::WindowText, Qt::green);
    Pal.setColor(QPalette::Normal, QPalette::Window, Qt::black);
    plot->setPalette(Pal);
    plot->setMinimumSize(800,200); //we set the minimum size of the plot
    //plot->setFixedSize(500,125);
    plot->setAxisScale(QwtPlot::xBottom,0,600);
    plot->setAxisScaleDraw(QwtPlot::xBottom, new RealScaleDraw(p_count, 1));
    plot->setAxisScaleDraw(QwtPlot::yLeft, new RealScaleDraw(p_count, 2));


    //plot->setTitle("T = f(t)"); //title of the graphe

    // axes names
    plot->setAxisTitle(QwtPlot::xBottom, "<font color = 'blue'>time (s)</font>");
    plot->setAxisTitle(QwtPlot::yLeft, "<font color = 'blue'>Flow velocity (mL/s)</font>");
//    QwtScaleWidget *qwtsw = plot->axisWidget(QwtPlot::xBottom);
//    QPalette palette = qwtsw->palette();



    // canvas properties
    plot->canvas()->setLineWidth( 1 );
    plot->canvas()->setFrameStyle( QFrame::Box | QFrame::Plain );
    plot->canvas()->setBorderRadius( 3 );

    // creation of the curve (you can add more curve to a graphe)
    curve = new QwtPlotCurve;
    curve->setPen(QPen(Qt::green));
    curve->attach(plot);

    //
    plot1 = new QwtPlot(this);
    QPalette Pal1 = plot1->palette();
    //Pal.setColor(QPalette::Normal, QPalette::WindowText, Qt::green);
    Pal1.setColor(QPalette::Normal, QPalette::Window, Qt::black);
    plot1->setPalette(Pal1);
    plot1->setMinimumSize(800,200); //we set the minimum size of the plot
    //plot1->setFixedSize(500,125);
    plot1->setAxisScale(QwtPlot::xBottom,0,600);
    plot1->setAxisScaleDraw(QwtPlot::xBottom, new RealScaleDraw(p_count, 1));
    plot1->setAxisScaleDraw(QwtPlot::yLeft, new RealScaleDraw(p_count, 2));

    //plot1->setTitle("T = f(t)"); //title of the graphe

    // axes names
    plot1->setAxisTitle(QwtPlot::xBottom, "<font color = 'blue'>time (s)</font>" );
    plot1->setAxisTitle(QwtPlot::yLeft, "<font color = 'blue'>Volume <br> (mL)</font>");

    //canvas properties
    plot1->canvas()->setLineWidth( 1 );
    plot1->canvas()->setFrameStyle( QFrame::Box | QFrame::Plain );
    plot1->canvas()->setBorderRadius( 3 );

    // creation of the curve (you can add more curve to a graphe)
    curve1 = new QwtPlotCurve;
    curve1->setPen(QPen(Qt::green));
    curve1->attach(plot1);
}

void Widget::my_compensate()
{

//    QString temp;
//    temp = lineedit->text();
//    compensate = temp.toInt();

}

void Widget::my_closetime()
{
//        QString temp;
//        temp = lineedit1->text();
//        close_time = temp.toInt();
}

void Widget::my_slider()
{
//    int temp;
//    temp = slider->value();
//    str_temp = QString(temp);
//    QTextStream out(stdout);
//    out<<temp<<endl;

}

void Widget::button_callback()
{
    button->setDisabled(1);
    button2->setEnabled(1);
    button1->setEnabled(1);

    QTextStream out(stdout);
    str_start = QString( "START ACQUISITION");
    out << str_start << endl;
    debugOutput(QtDebugMsg, str_start);

    my_time1.start();   //start elipse time1
    restart = 1;

}

void Widget::button2_callback()
{
    button2->setDisabled(1);
    button->setEnabled(1);
    button1->setDisabled(1);

    QTextStream out(stdout);
    QString b;
    b = QString::number(my_time1.elapsed()/1000.000, 'f', 3);
    str_stop = QString( b + QString("s") + QString(" ") + QString("STOP ACQUISITION"));
    out << str_stop << endl;
    debugOutput(QtDebugMsg, str_stop);

}

void Widget::receive()
{
    if (button->isEnabled() == 0) {
    char data[255]; //creation of a char aray
    int bytesRead = port->read(data, 255); //load the port data
    data[bytesRead] = '\0'; //end the char aray


    //we convert the char into a integer
    int i=0;
    QString temp;
    temp = lineedit->text();
    compensate = temp.toInt();
    if (bytesRead==1)
    {
        i = data[0] + compensate;
        if (i < 3 && i >-3){
            i=0;           
    }

    }else return; // if the data size is different from 1 => exit the function


    //QTextStream out(stdout);
    //out << data << " (" << bytesRead << " bytes) understood :" << i<< endl; //writing the data read in the console

    //upper edge enable
    slidev = slider->value();
    if (abs(i)<slidev) {
        upedge();
        en_start=1;
    }

    //enable start acquisition
//    if (en_start==1) {
    addpoint(i); //we add a point to the graphe
//    }

    int elapsed_time1 = my_time1.elapsed();
    lcd1->display(QString::number( elapsed_time1/1000, 'f', 1));
    if (elapsed_time1/1000 >= 60) {
        button2->click();
    }
    //QTextStream out(stdout);
    //out << elapsed_time1 << endl;
    }
}


void Widget::addpoint(int point)
{
    // suppress data amplitude, not in version I
    if (my_timer->isActive()) {
        point /= 10;
    }

    ysum += point;
    data_x->push_back(data_x->size());// add the point to the data
    data_y->push_back(point);
    data_ysum->push_back(ysum);

    if (restart == 1) {            // recount after a new start, all data will be disrupted

        ysum = 0;
        data_x->clear();
        data_y->clear();
        data_ysum->clear();
        restart = 0;
    }
    if (data_x->size() == 600){

        data_x->clear();
        data_y->clear();
        data_ysum->clear();
        p_count++;     //to next 30s
        plot->setAxisScaleDraw(QwtPlot::xBottom, new RealScaleDraw(p_count, 1));  //redraw axes
        plot1->setAxisScaleDraw(QwtPlot::xBottom, new RealScaleDraw(p_count, 1));
    }

    // to write_to_file

    QString temp1 = QString::number(ysum);
    sum = QString (sum + "\n" + temp1);

    QString temp2 = QString::number(point);
    y = QString (y + "\n" + temp2);

    curve->setSamples(*data_x,*data_y);// we set the data to the curve

//   plot->setAxisScale(QwtPlot::xBottom,0,600);
//   plot->setAxisScaleDraw(QwtPlot::xBottom, new RealScaleDraw(p_count, 1));
//   plot->setAxisAutoScale(QwtPlot::yLeft);



//    QList<double> ticks[QwtScaleDiv::NTickTypes];
//    ticks[QwtScaleDiv::MajorTick] << 60 << 120;

//    QwtScaleDiv scaleDiv(
//        ticks[QwtScaleDiv::MajorTick].first(),
//        ticks[QwtScaleDiv::MajorTick].last(),
//        ticks );

//    plot->setAxisScaleDiv(QwtPlot::xBottom, scaleDiv);



    //plot->setAxisScaleDraw(QwtPlot::xBottom, xscale);
    plot->updateAxes();
    plot->replot(); // we redraw the graphe

    curve1->setSamples(*data_x,*data_ysum);// we set the data to the curve

    //QTextStream out(stdout);
    //out << sum << endl;


    // plot1->setAxisScale(QwtPlot::xBottom,0,600);
    // plot1->setAxisScaleDraw(QwtPlot::xBottom, new RealScaleDraw(p_count, 1));
    //plot1->setAxisAutoScale(QwtPlot::yLeft);
    plot1->updateAxes();
    plot1->replot(); // we redraw the graph
}

void Widget::transmitCmd()
{

  value = 1; //click close button

}

void Widget::upedge()
{
    int upedge = 1;//upper edge detected
    value1 = value*upedge; //send high level

if (value1 == 1) {
char buf;
buf=(char)value1;
port->write(&buf,1);// send the buffer

label->setText("<font size=10>Status \n closed</font>");

QTextStream out(stdout);
QString temp;
temp = QString::number(my_time1.elapsed()/1000.000, 'f', 3);
temp = QString( temp + QString("s") + QString(" ") + QString("SEND HIGH"));
out << temp << endl;
debugOutput(QtDebugMsg, temp);


 str1 = temp;
 my_time.start();
 my_timer->start();

 button1->setDisabled(1);
 value1 = 0; //reset
}
upedge = 0; //reset
value = 0; //reset
}

void Widget::my_timer_func()
{

    int elapsed_time = my_time.elapsed();
    lcd->display(QString::number( elapsed_time/1000.0, 'f', 1));

    QString temp;
    temp = lineedit1->text();
    close_time = temp.toInt();
    if (elapsed_time >= close_time*1000){
        my_timer->stop();
        transmitCmd1();
        button1->setEnabled(1);
        return; }
}

void Widget::transmitCmd1()

{
    char buf;

    //value = 0; //reset
    buf = (char)value;
    port->write(&buf,1);

    label->setText("<font size=10>Status \n open</font>");

    QTextStream out(stdout);
    QString temp;
    temp = QString::number(my_time1.elapsed()/1000.000, 'f', 3);
    temp = QString( temp + QString("s") + QString(" ") + QString("SEND LOW"));
    out << temp << endl;
    debugOutput(QtDebugMsg, temp);

//     str2 = temp;
//     if (str_close.isEmpty() == 1) {
//     str_close = QString(str1 + QString("\n") + str2);
//     }
//     else {
//         str_close = QString(str_close + QString("\n") + str1 + QString("\n") + str2);
//     }
}

void Widget::debugOutput(QtMsgType type, QString msg)
{
    QString timestring = qApp->property("my_global_prefix").toString();
    QFile debugfile("data/" + timestring + "/debug.txt");
        debugfile.open(QIODevice::WriteOnly | QIODevice::Text  | QIODevice::Append);

        switch (type)
        {
            case QtDebugMsg:
                {
                QTextStream out(&debugfile);
                out << msg << endl;
                }
                break;


            default :
                break;

        }

        debugfile.flush();
        debugfile.close();

}
