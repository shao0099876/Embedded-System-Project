#include<stdio.h>
#include<fcntl.h>
#include<sys/ioctl.h>
#include<unistd.h>
#include<QTextCodec>
#include"YJSQLite.h"
#include "/arm2410cl/sqlite/sqlite/sqlite3.h"
#include"myqtc1.h"
MyDlg::MyDlg()
{
	ui.setupUi(this);
	QObject::connect(ui.pushButton, SIGNAL(clicked()),this,SLOT(Seclect()));
	QObject::connect(ui.pushButton_2, SIGNAL(clicked()),this,SLOT(Seclectold()));
	//ui.textEdit_2->setText("name#sex#age#phone#address#relation\n");//测试
}
void MyDlg::Seclect()
{	
	sqliteDB_open();
	char* a=sqliteDB_opt_select_alluser();
	sqliteDB_close();
	ui.textEdit->setText(a);
}

void MyDlg::Seclectold()
{	
	sqliteDB_open();
	char* a=sqliteDB_opt_select_allolduser();
	sqliteDB_close();
	//ui.textEdit_2->setText("name#sex#age#address#state\n");//测试
	ui.textEdit->append(a);
}

