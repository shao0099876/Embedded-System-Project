/********************************************************************************
** Form generated from reading ui file 'untitled.ui'
**
** Created: Wed Jun 26 15:28:57 2019
**      by: Qt User Interface Compiler version 4.4.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_UNTITLED_H
#define UI_UNTITLED_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QTableWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label;
    QTableWidget *oldtable;
    QTableWidget *usertable;
    QPushButton *pushButton_4;
    QTableWidget *tableWidget;

    void setupUi(QWidget *Form)
    {
    if (Form->objectName().isEmpty())
        Form->setObjectName(QString::fromUtf8("Form"));
    Form->resize(663, 475);
    pushButton = new QPushButton(Form);
    pushButton->setObjectName(QString::fromUtf8("pushButton"));
    pushButton->setGeometry(QRect(10, 370, 131, 41));
    pushButton_2 = new QPushButton(Form);
    pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
    pushButton_2->setGeometry(QRect(190, 380, 131, 41));
    label = new QLabel(Form);
    label->setObjectName(QString::fromUtf8("label"));
    label->setGeometry(QRect(450, 230, 171, 101));
    oldtable = new QTableWidget(Form);
    if (oldtable->columnCount() < 5)
        oldtable->setColumnCount(5);
    QTableWidgetItem *__colItem = new QTableWidgetItem();
    oldtable->setHorizontalHeaderItem(0, __colItem);
    QTableWidgetItem *__colItem1 = new QTableWidgetItem();
    oldtable->setHorizontalHeaderItem(1, __colItem1);
    QTableWidgetItem *__colItem2 = new QTableWidgetItem();
    oldtable->setHorizontalHeaderItem(2, __colItem2);
    QTableWidgetItem *__colItem3 = new QTableWidgetItem();
    oldtable->setHorizontalHeaderItem(3, __colItem3);
    QTableWidgetItem *__colItem4 = new QTableWidgetItem();
    oldtable->setHorizontalHeaderItem(4, __colItem4);
    if (oldtable->rowCount() < 1)
        oldtable->setRowCount(1);
    QTableWidgetItem *__rowItem = new QTableWidgetItem();
    oldtable->setVerticalHeaderItem(0, __rowItem);
    oldtable->setObjectName(QString::fromUtf8("oldtable"));
    oldtable->setGeometry(QRect(0, 280, 441, 91));
    usertable = new QTableWidget(Form);
    if (usertable->columnCount() < 6)
        usertable->setColumnCount(6);
    QTableWidgetItem *__colItem5 = new QTableWidgetItem();
    usertable->setHorizontalHeaderItem(0, __colItem5);
    QTableWidgetItem *__colItem6 = new QTableWidgetItem();
    usertable->setHorizontalHeaderItem(1, __colItem6);
    QTableWidgetItem *__colItem7 = new QTableWidgetItem();
    usertable->setHorizontalHeaderItem(2, __colItem7);
    QTableWidgetItem *__colItem8 = new QTableWidgetItem();
    usertable->setHorizontalHeaderItem(3, __colItem8);
    QTableWidgetItem *__colItem9 = new QTableWidgetItem();
    usertable->setHorizontalHeaderItem(4, __colItem9);
    QTableWidgetItem *__colItem10 = new QTableWidgetItem();
    usertable->setHorizontalHeaderItem(5, __colItem10);
    if (usertable->rowCount() < 2)
        usertable->setRowCount(2);
    QTableWidgetItem *__rowItem1 = new QTableWidgetItem();
    usertable->setVerticalHeaderItem(0, __rowItem1);
    QTableWidgetItem *__rowItem2 = new QTableWidgetItem();
    usertable->setVerticalHeaderItem(1, __rowItem2);
    usertable->setObjectName(QString::fromUtf8("usertable"));
    usertable->setGeometry(QRect(0, 170, 441, 101));
    pushButton_4 = new QPushButton(Form);
    pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
    pushButton_4->setGeometry(QRect(490, 170, 80, 27));
    tableWidget = new QTableWidget(Form);
    if (tableWidget->columnCount() < 6)
        tableWidget->setColumnCount(6);
    QTableWidgetItem *__colItem11 = new QTableWidgetItem();
    tableWidget->setHorizontalHeaderItem(0, __colItem11);
    QTableWidgetItem *__colItem12 = new QTableWidgetItem();
    tableWidget->setHorizontalHeaderItem(1, __colItem12);
    QTableWidgetItem *__colItem13 = new QTableWidgetItem();
    tableWidget->setHorizontalHeaderItem(2, __colItem13);
    QTableWidgetItem *__colItem14 = new QTableWidgetItem();
    tableWidget->setHorizontalHeaderItem(3, __colItem14);
    QTableWidgetItem *__colItem15 = new QTableWidgetItem();
    tableWidget->setHorizontalHeaderItem(4, __colItem15);
    QTableWidgetItem *__colItem16 = new QTableWidgetItem();
    tableWidget->setHorizontalHeaderItem(5, __colItem16);
    if (tableWidget->rowCount() < 1)
        tableWidget->setRowCount(1);
    QTableWidgetItem *__rowItem3 = new QTableWidgetItem();
    tableWidget->setVerticalHeaderItem(0, __rowItem3);
    tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
    tableWidget->setGeometry(QRect(0, 30, 631, 111));

    retranslateUi(Form);

    QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
    Form->setWindowTitle(QApplication::translate("Form", "Form", 0, QApplication::UnicodeUTF8));
    pushButton->setText(QApplication::translate("Form", "selectuser", 0, QApplication::UnicodeUTF8));
    pushButton_2->setText(QApplication::translate("Form", "selectold", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("Form", "160400202 \346\235\250\350\233\237\n"
"160400209 \345\210\230\350\275\251\n"
"160400618 \351\202\265\350\213\245\345\277\261", 0, QApplication::UnicodeUTF8));
    oldtable->horizontalHeaderItem(0)->setText(QApplication::translate("Form", "name", 0, QApplication::UnicodeUTF8));
    oldtable->horizontalHeaderItem(1)->setText(QApplication::translate("Form", "sex", 0, QApplication::UnicodeUTF8));
    oldtable->horizontalHeaderItem(2)->setText(QApplication::translate("Form", "age", 0, QApplication::UnicodeUTF8));
    oldtable->horizontalHeaderItem(3)->setText(QApplication::translate("Form", "address", 0, QApplication::UnicodeUTF8));
    oldtable->horizontalHeaderItem(4)->setText(QApplication::translate("Form", "state", 0, QApplication::UnicodeUTF8));
    oldtable->verticalHeaderItem(0)->setText(QApplication::translate("Form", "old", 0, QApplication::UnicodeUTF8));
    usertable->horizontalHeaderItem(0)->setText(QApplication::translate("Form", "name", 0, QApplication::UnicodeUTF8));
    usertable->horizontalHeaderItem(1)->setText(QApplication::translate("Form", "sex", 0, QApplication::UnicodeUTF8));
    usertable->horizontalHeaderItem(2)->setText(QApplication::translate("Form", "age", 0, QApplication::UnicodeUTF8));
    usertable->horizontalHeaderItem(3)->setText(QApplication::translate("Form", "phone", 0, QApplication::UnicodeUTF8));
    usertable->horizontalHeaderItem(4)->setText(QApplication::translate("Form", "addres", 0, QApplication::UnicodeUTF8));
    usertable->horizontalHeaderItem(5)->setText(QApplication::translate("Form", "relation", 0, QApplication::UnicodeUTF8));
    usertable->verticalHeaderItem(0)->setText(QApplication::translate("Form", "user", 0, QApplication::UnicodeUTF8));
    usertable->verticalHeaderItem(1)->setText(QApplication::translate("Form", "user", 0, QApplication::UnicodeUTF8));
    pushButton_4->setText(QApplication::translate("Form", "GPS", 0, QApplication::UnicodeUTF8));
    tableWidget->horizontalHeaderItem(0)->setText(QApplication::translate("Form", "addrname", 0, QApplication::UnicodeUTF8));
    tableWidget->horizontalHeaderItem(1)->setText(QApplication::translate("Form", "longitude", 0, QApplication::UnicodeUTF8));
    tableWidget->horizontalHeaderItem(2)->setText(QApplication::translate("Form", "latitude", 0, QApplication::UnicodeUTF8));
    tableWidget->horizontalHeaderItem(3)->setText(QApplication::translate("Form", "high", 0, QApplication::UnicodeUTF8));
    tableWidget->horizontalHeaderItem(4)->setText(QApplication::translate("Form", "speed", 0, QApplication::UnicodeUTF8));
    tableWidget->horizontalHeaderItem(5)->setText(QApplication::translate("Form", "time", 0, QApplication::UnicodeUTF8));
    tableWidget->verticalHeaderItem(0)->setText(QApplication::translate("Form", "GPS", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(Form);
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UNTITLED_H
