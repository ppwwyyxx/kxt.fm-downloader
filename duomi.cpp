#include "MyUi.h"

int main ( int argc, char *argv[] ) {
	QApplication my(argc, argv);
	MyWin win;
	win.setWindowIcon(QIcon(QString("0.ico")));
	win.show();
	return my.exec();
}
