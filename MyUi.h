// $File: MyUi.h
// $Date: Sun Oct 28 11:35:34 2012 +0800
// Author: Yuxin Wu <ppwwyyxxc@gmail.com>
#ifndef H_DUOMI_UI
#define H_DUOMI_UI
#include <QApplication>
#include <QNetworkAccessManager>
#include <QtNetwork>
#include <QNetworkCookieJar>
#include <QFileDialog>
#include <QNetworkRequest>
#include "base64/base64.h"
#include "ui_duomi.h"
#include <fstream>
#include <iostream>
using namespace std;

class MyWin: public QMainWindow, public Ui::MainWindow{
	Q_OBJECT QString refUrl, downloadUrl;
	QNetworkAccessManager * downloader;
	ofstream fout;
	QNetworkReply * page;
	QNetworkReply * data;
	bool getUrl();

	public:
		MyWin();
		void print_msg(const QString & msg);
	public slots:
		void downloadPage();
		void downloadError();
		void downloadData();
		void allFinished();
		void setProgress(qint64 value, qint64 total);
};

#endif
