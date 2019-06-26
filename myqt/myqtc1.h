#ifndef __DLG_H_
#define __DLG_H_
#include<QDialog>

#include"ui_untitled.h"
class MyDlg : public QDialog
{
	Q_OBJECT
	public:
		MyDlg();
	public slots:
		void Seclect();
		void Seclectold();
		void web();
	private:
		Ui::Form ui;
};
#endif
