#include "client.h"

Client::Client(QObject* parent): QObject(parent)
{
    connect(&client, SIGNAL(connected()), this, SLOT(startTransfer()));
    pba = 0;
}

Client::~Client()
{
    client.close();
}

void Client::start(QString address, quint16 port)
{
    QHostAddress addr(address);
    client.connectToHost(addr, port);
}

void Client::SetImageData(QByteArray* pba_)
{
    pba = pba_;
}

void Client::startTransfer()
{
    //if (pba) qDebug() << client.write(*pba);
    //if (pba) qDebug() << client.write(*pba, pba->size());
    //qDebug() << pba->size();
    if (pba) client.write(*pba, pba->size());
}
