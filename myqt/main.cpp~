#include <QApplication>
#include <QTextCodec>
#include <pthread.h>
#include"myqtc1.h"
#include"gps.h"
int main(int argc, char **argv)
{
	//创建线程调用gps获取地点信息
	pthread_t th_gps;	
	pthread_create(&th_gps, NULL,start, 0);
	//start();
	QApplication app(argc,argv);
	MyDlg *mydlg = new MyDlg;	
		//QTextCodec *codec = QTextCodec::codecForName("UTF-8");
		//QTextCodec::setCodecForTr(codec);
		//QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());
		QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
	mydlg->setFont(QFont("unifont",16,QFont::Normal));
	return mydlg->exec();
}
