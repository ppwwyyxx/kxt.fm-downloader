// $File: kxtfm.cpp
// $Date: Sun Oct 28 01:43:48 2012 +0800
// Author: Yuxin Wu <ppwwyyxxc@gmail.com>
#include "MyUi.h"

int main ( int argc, char *argv[] ) {
	QApplication my(argc, argv);
	MyWin win;
	win.setWindowIcon(QIcon(QString("0.ico")));
	win.show();
	return my.exec();
}
