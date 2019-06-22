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
}
void MyDlg::Seclect()
{	
	//QTextCodec codec=QTextCodec::codecForLocale();
	//QString a=codec->toUnicode(sqliteDB_opt_select_alluser());
	char a=sqliteDB_opt_select_alluser();
	ui.textEdit->setText((char*)a);
}
