#pragma once
#include <QtNetwork>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QImage>
#include <QPaintDevice>
#include <QLabel>
#include <QStatusBar>
#include <QTimer>
#include <QTime>

class Server: public QObject
{
Q_OBJECT
public:
  Server(QObject * parent = 0);
  void setLabel(QLabel* label);
  void setStatusBar(QStatusBar* StatusBar);
  QPixmap getPixMap();
  ~Server();
public slots:
  void acceptConnection();
  void startRead();
  void timeIsOver();
private:
  QTcpServer server;
  QTcpSocket* client;
  QLabel* pLabel;
  QStatusBar* pStatusBar;
  QPixmap NewPixMap;
  QTimer *tmr;
  bool StartRead;
  QByteArray bufferAll;
};
