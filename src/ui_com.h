/********************************************************************************
** Form generated from reading UI file 'com.ui'
**
** Created: Mon Sep 24 17:22:17 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COM_H
#define UI_COM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_COM
{
public:
    QComboBox *comboBox;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QDialog *COM)
    {
        if (COM->objectName().isEmpty())
            COM->setObjectName(QString::fromUtf8("COM"));
        COM->resize(258, 301);
        comboBox = new QComboBox(COM);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(60, 60, 131, 22));
        pushButton = new QPushButton(COM);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(100, 250, 61, 21));
        pushButton_2 = new QPushButton(COM);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(180, 250, 61, 21));

        retranslateUi(COM);

        QMetaObject::connectSlotsByName(COM);
    } // setupUi

    void retranslateUi(QDialog *COM)
    {
        COM->setWindowTitle(QApplication::translate("COM", "Select a port", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("COM", "OK", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("COM", "Cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class COM: public Ui_COM {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COM_H
