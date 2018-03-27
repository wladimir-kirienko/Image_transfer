#include "server.h"


Server::Server(QObject* parent): QObject(parent)
{
  connect(&server, SIGNAL(newConnection()),
    this, SLOT(acceptConnection()));

  server.listen(QHostAddress::Any, 8888);

  tmr = new QTimer();
  tmr->setInterval(1000);
  connect(tmr, SIGNAL(timeout()), this, SLOT(timeIsOver()));

  StartRead = false;
}

void Server::setLabel(QLabel *label)
{
    pLabel = label;
}

void Server::setStatusBar(QStatusBar *StatusBar)
{
    pStatusBar = StatusBar;
}

QPixmap Server::getPixMap()
{
    return NewPixMap;
}

Server::~Server()
{
  server.close();
  //delete pImage;
}

void Server::acceptConnection()
{
  client = server.nextPendingConnection();

  connect(client, SIGNAL(readyRead()), this, SLOT(startRead()));
}

void Server::timeIsOver()
{
    QBuffer buffer(&bufferAll);

    if (bufferAll.isEmpty())
        return;

    QImage myImage;
    myImage.load(&buffer, "PNG");
    NewPixMap.convertFromImage(myImage,Qt::ColorOnly);
    pLabel->setPixmap(NewPixMap);
    pStatusBar->showMessage("Изображение получено");
    StartRead = false;
    client->close();
}


void Server::startRead()
{
    if (!StartRead){
        tmr->start();
        bufferAll.clear();
        StartRead = true;
    }

    QByteArray ba;

    while (client->bytesAvailable())
    {
        ba = client->readAll();
        //qDebug() << ba.size();
        bufferAll.append(ba);
    }

    //qDebug() << "Total: " << bufferAll.size();
}

