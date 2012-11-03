#ifndef H_DUOMI_UI
#define H_DUOMI_UI
#include <QApplication>
#include <QNetworkAccessManager>
#include <QtNetwork>
#include <QNetworkCookieJar>
#include <QFileDialog>
#include <QNetworkRequest>
#include "ui_duomi.h"
#include <fstream>
#include <iostream>
using namespace std;

class MyWin: public QMainWindow, public Ui::MainWindow {
	Q_OBJECT QString RealUrl;
	QNetworkAccessManager *downloader;
	ofstream fout;
	QNetworkReply *page;
	QNetworkReply *data;
	bool getUrl();

	public:
		MyWin();
		void print_msg(const QString & msg);
	public slots:
		void downloadPage();
		void downloadError(QString);
		void downloadData();
		void allFinished();
		void setProgress(qint64, qint64);
		void restore();
};

#endif
