#include "com.h"
#include "ui_com.h"




COM::COM(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::COM)
{
    ui->setupUi(this);

    for (int i=1; i<20; i++){
    ui->comboBox->addItem("COM" + QString::number(i));
    ui->comboBox->setCurrentIndex(3);

}
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(button_callback()));
    //connect(ui->pushButton, SIGNAL(destroy()),this, SLOT(button_callback()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(close()));

}

COM::~COM()
{

    delete ui;
}


void COM::button_callback()
{

    QString com;
    com = ui->comboBox->currentText();
    qApp->setProperty("my_global_string", com);

    //QWidget::activateWindow();
    //COM->close();

//    QTextStream out(stdout);
//    out << com;

    show_widget();
}

void COM::show_widget()
{

    qApp->setProperty("my_close_dialog", 0);   // reset COM signal not to close main dialog
    Widget w;
    QPalette Pal = w.palette();
    //Pal.setColor(QPalette::Normal, QPalette::WindowText, Qt::green);
    Pal.setColor(QPalette::Normal, QPalette::Window, Qt::gray);
    w.setPalette(Pal);

    //w.exec();
    if (qApp->property("my_close_dialog") == 0) {

    this->close();
    //w.setModal(false);
    w.exec();

    }


}

//void COM::init_port()
//{
//    QextSerialPort *port;
//    //QTextStream out(stdout);//creation of a stream belonging to the console (you have to activate the console in the .pro file to display it)

//    QString portname = ui->comboBox->currentText();
//    port = new QextSerialPort(portname, QextSerialPort::EventDriven); //we create the port

//    port->open(QIODevice::ReadWrite | QIODevice::Unbuffered); //we open the port
//    if(!port->isOpen())
//    {
//        QMessageBox::warning(COM, "port error", "Impossible to open the port " +portname +"!");
//    }


//    //we set the port properties
//    port->setBaudRate(BAUD9600);//modify the port settings on your own
//    port->setFlowControl(FLOW_OFF);
//    port->setParity(PAR_NONE);
//    port->setDataBits(DATA_8);
//    port->setStopBits(STOP_1);

//    //str = "port open";
//    //out << str << endl; // we write on the console


//}
