// $File: MyUi.cpp
// $Date: Sun Oct 28 11:37:09 2012 +0800
// Author: Yuxin Wu <ppwwyyxxc@gmail.com>
#include "MyUi.h"

MyWin::MyWin(){
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8")); // Chinese Support
	setupUi(this);
	downloader = new QNetworkAccessManager;
	downloader->setCookieJar(new QNetworkCookieJar);
	connect(lineEdit, SIGNAL(returnPressed()),
			this, SLOT(downloadPage()));
	page = data = NULL;
}

bool MyWin::getUrl(){
	QByteArray html = page->readAll();
	int index_ = html.indexOf("soundFile:\"");
	if(index_ != -1){
		index_ += strlen("soundFile:\"");
		QByteArray encoded;
		for(;html[index_] != '"';index_++)
			encoded += html[index_];
		downloadUrl = QString(base64_decode(encoded.data()).c_str());
		return true;
	}
	return false;
}

void MyWin::print_msg(const QString & msg){
	setWindowTitle(msg);
}

void MyWin::downloadPage(){
	if(page!=NULL)
		delete page;
	if(data!=NULL)
		delete data;
	lineEdit->setEnabled(false);
    label_3->setPixmap(QPixmap());
	page = data = NULL;
	refUrl = QString("http://") + label_2->text() + lineEdit->text();
	cout << "Page: " << refUrl.toStdString() << endl;
	page = downloader->get(QNetworkRequest(QUrl(refUrl)));
	connect(page, SIGNAL(finished()),
			this, SLOT(downloadData()));
}

void MyWin::downloadError(){//QNetworkReply::NetworkError code_){
	lineEdit->setEnabled(true);
    label_3->setPixmap(QPixmap(QString::fromUtf8("sun.jpg")));
	fout.close();
	print_msg(QString::fromUtf8("Errors Occurred"));
//			if(page!=NULL)
////				page->deleteLater();
//				delete page;
//			if(data!=NULL)
////				data->deleteLater();
//				delete data;
}

void MyWin::downloadData(){
	if( page->error() != QNetworkReply::NoError ){
		downloadError();
		return;
	}
	if(!getUrl()){
		downloadError();//QNetworkReply::NoError);
		return;
	}
	print_msg(QString("URL found: ") + downloadUrl );
	cout << "URL found: " + downloadUrl.toStdString()  << endl;

	QString m_dir = QFileDialog::getExistingDirectory (0, "Choose a place to download..", QDir::homePath() + QString("/Desktop"), QFileDialog::ShowDirsOnly );
	if (m_dir == ""){
		lineEdit->setEnabled(true);
		label_3->setPixmap(QPixmap(QString::fromUtf8("sun.jpg")));
		return;
	}

	string file_path = m_dir.toStdString() + "/" + downloadUrl.split("/").last().toStdString();
	fout.open(file_path.c_str(), ios::binary | ios::out);
	// set header
	QNetworkRequest header;
	header.setUrl(QUrl(downloadUrl));
	header.setRawHeader("Accept-Charset", "Accept-Charset: ISO-8859-1,utf-8;q=0.7,*;q=0.3");
	header.setRawHeader("Accept-Language", "en-us,en;q=0.8");
	header.setRawHeader("Connection", "keep-alive");
	header.setRawHeader("User-Agent", "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.4 (KHTML, like Gecko) Chrome/22.0.1229.94 Safari/537.4");
	header.setRawHeader("Referer", "http://ear.duomi.com/wp-content/plugins/audio-player/assets/player.swf?ver=2.0.4.1");

	// start download
	data = downloader->get(header);
	connect(data, SIGNAL(downloadProgress(qint64, qint64)),
			this, SLOT(setProgress(qint64, qint64)));
	connect(data, SIGNAL(finished()),
			this, SLOT(allFinished()));
}

void MyWin::setProgress(qint64 value, qint64 total){
	QByteArray s = data->readAll();
	fout.write(s.data(), s.size());
	progressBar->setTextVisible("true");
	progressBar->setMaximum(total);
	progressBar->setValue(value);
}

void MyWin::allFinished(){
	if( data->error() != QNetworkReply::NoError ){
		downloadError();
		return;
	}
	fout.close();
	lineEdit->setEnabled(true);
    label_3->setPixmap(QPixmap(QString::fromUtf8("sun.png")));
	print_msg(QString("Done!"));
//	if(page!=NULL)
//		page->deleteLater();
//	if(data!=NULL)
//		data->deleteLater();
}

