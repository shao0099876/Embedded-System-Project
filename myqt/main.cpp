#include<QApplication>
#include<QTextCodec>
#include"myqtc1.h"
int main(int argc, char **argv)
{
	QApplication app(argc,argv);
	MyDlg *mydlg = new MyDlg;	
	QTextCodec *codec = QTextCodec::codecForName("UTF-8");
	QTextCodec::setCodecForTr(codec);
	QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());
	QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
	mydlg->setFont(QFont("unifont",16,QFont::Normal));
	return mydlg->exec();
}
