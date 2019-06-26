#include<stdio.h>
#include<fcntl.h>
#include<sys/ioctl.h>
#include<unistd.h>
#include<QTextCodec>
#include<QtWebKit>
#include"YJSQLite.h"
#include"myqtc1.h"
MyDlg::MyDlg()
{
	ui.setupUi(this);
	QObject::connect(ui.pushButton, SIGNAL(clicked()),this,SLOT(Seclect()));
	QObject::connect(ui.pushButton_2, SIGNAL(clicked()),this,SLOT(Seclectold()));
   //QObject::connect(ui.pushButton_3, SIGNAL(clicked()),this,SLOT(path()));
	QObject::connect(ui.pushButton_4, SIGNAL(clicked()),this,SLOT(web()));
}
void MyDlg::Seclect()
{	
	sqliteDB_open();
	char* a=sqliteDB_opt_select_alluser();
	sqliteDB_close();
	//table
	char *s1;
	int i=1;
	s1=strtok(a,"#");
	ui.usertable->setItem(0,0,new QTableWidgetItem(s1));//hang lie
	while(s1!=NULL){
		//printf("%s\n",s1);
		s1=strtok(NULL,"#");		
		ui.usertable->setItem(0,i,new QTableWidgetItem(s1));
		i++;
	}
	
}

void MyDlg::Seclectold()
{	
	sqliteDB_open();
	char* a=sqliteDB_opt_select_allolduser();
	sqliteDB_close();
	char *s1;
	int i=1;
	s1=strtok(a,"#");
	ui.oldtable->setItem(0,0,new QTableWidgetItem(s1));//hang lie
	while(s1!=NULL){
		//printf("%s\n",s1);
		s1=strtok(NULL,"#");		
		ui.oldtable->setItem(0,i,new QTableWidgetItem(s1));
		i++;
	}
}

/*void MyDlg::path()
{	
	sqliteDB_open();
	char* s=sqliteDB_opt_select_newpath();
	sqliteDB_close();
	ui.textEdit_2->setText(s);
}*/

void MyDlg::web()
{	
	//ui.tableWidget->clearContents();
	sqliteDB_open();
	char* s=sqliteDB_opt_select_newpath();
	sqliteDB_close();	
	char *s1;
	int i=1;
	s1=strtok(s,"#");
	ui.tableWidget->setItem(0,0,new QTableWidgetItem(s1));//hang lie
	while(s1!=NULL){
		//printf("%s\n",s1);
		s1=strtok(NULL,"#");		
		ui.tableWidget->setItem(0,i,new QTableWidgetItem(s1));
		i++;
	}

	//sqliteDB_open();
	//char* a=sqliteDB_opt_select_newpath();
	//sqliteDB_close();
	//ui.textEdit->setText(a);//测试
}


