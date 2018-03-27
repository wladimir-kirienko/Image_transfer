#pragma once
#include <QtNetwork>
#include <QObject>
#include <QString>
#include <QTcpSocket>
#include <QHostAddress>

class Client: public QObject
{
Q_OBJECT
public:
  Client(QObject* parent = 0);
  ~Client();
  void start(QString address, quint16 port);
  void SetImageData(QByteArray* pba_);
public slots:
  void startTransfer();
private:
  QTcpSocket client;
  QByteArray* pba;
};
