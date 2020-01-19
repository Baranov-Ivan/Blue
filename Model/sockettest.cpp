#include "sockettest.h"
#include "Collections.h"
#include <QTimer>

SocketTest::SocketTest(QObject *parent) : QObject(parent)
{
}

void SocketTest::Connect()
{
    socket = new QTcpSocket(this);
    connect(socket,SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnect()));
    socket->setSocketOption(QAbstractSocket::LowDelayOption, 1);
    socket->connectToHost("wgforge-srv.wargaming.net", 443);
    //TryConnect();
    if(socket->waitForConnected(10000))
    {
        qDebug() << "Connected!";
    }
    else
    {
        qDebug() << "Not connected!";
    }
}

void SocketTest::SendMessage(Actions Action, QJsonObject jsonObj)
{
    if(socket->isOpen())
    {
       socket->write(toMessageFormat(Action,jsonObj));
       socket->waitForReadyRead(5000); // было 900
    } else {
        qDebug() << "socket is close";
    }
}


void SocketTest::readyRead()
{
    QByteArray buffer = socket->readAll();
    while(buffer.size() < 8)
    {
        if(socket->waitForReadyRead(5000)) // было 900
        {
            buffer.append(socket->readAll());
        }
    }

    QByteArray resultCode = buffer.mid(0,4);
    QByteArray sizeOfData = buffer.mid(4,4);
    QByteArray data = buffer.mid(8,buffer.size()-8);

    QDataStream in(sizeOfData);
    in.setByteOrder(QDataStream::LittleEndian);
    int int_sizeOfData;
    in >> int_sizeOfData;

    QDataStream code(resultCode);
    code.setByteOrder(QDataStream::LittleEndian);
    int int_code;
    code >> int_code;
    this->code = static_cast<Result>(int_code);

    qDebug() << resultCode;
    Data = data;
    while(Data.size() < int_sizeOfData) {
        if(socket->waitForReadyRead(5000)) //было 900
            Data.append(socket->readAll());
    }
    qDebug() << Data;
    doc = QJsonDocument::fromJson(Data, &docError);
    //code = QJsonA::fromJson(resultCode, &codeError);
}


void SocketTest::disconnect()
{
    socket->deleteLater();
}

QByteArray SocketTest::toMessageFormat(Actions Action,QJsonObject jsonObj) {

    QByteArray jsonData = QJsonDocument(jsonObj).toJson(QJsonDocument::Compact);

    int int_action = Action;
    int* action = &int_action;
    int int_jsonSize = jsonData.size();
    int* jsonSize = &int_jsonSize;
    int zero_int = 0;
    int* zero_size = &zero_int;

    QByteArray bytes_action((char*)action,4);
    QByteArray bytes_jsonSize((char*)jsonSize,4);
    QByteArray bytes_zeroSize((char*)zero_size,4);
    qDebug() << jsonData;
    if(int_jsonSize > 4)
        return bytes_action + bytes_jsonSize + jsonData;
    else
        return bytes_action + bytes_zeroSize;
}

QJsonDocument SocketTest::getterDoc()
{
    return this->doc;
}

void SocketTest::sendMoveMessage(int line_idx,int speed, int train_idx) {
    QJsonObject moveObj;
    moveObj.insert("line_idx",QJsonValue::fromVariant(line_idx));
    moveObj.insert("speed",QJsonValue::fromVariant(speed));
    moveObj.insert("train_idx",QJsonValue::fromVariant(train_idx));

    SendMessageWOW(MOVE,moveObj);
}

void SocketTest::sendTurnMessage() {
    SendMessageWOW(TURN,{});
    /*if(this->socket->isOpen())
    {
        this->socket->write(toMessageFormat(TURN,{}));
    }*/
    /*while(code != OKEY) {
        qDebug() << code;
        qDebug() <<"Number";
        socket->waitForReadyRead(500);
    }*/
}

SocketTest::~SocketTest() {
    this->socket->close();
    qDebug()<<"Destructed";
}

void SocketTest::SendMessageWOW(Actions Action, QJsonObject jsonObj)
{
    if(socket->isOpen())
    {
        if(Action == TURN)
        {
            connect(socket,SIGNAL(readyRead()),this,SLOT(dataArrived()));
            socket->write(toMessageFormat(Action,jsonObj));
        } else {
            socket->write(toMessageFormat(Action,jsonObj));
            socket->waitForReadyRead(5000); // было 750
        }
    } else {
        qDebug() << "socket is close";
    }
}

void SocketTest::sendUpgradeMessage(bool upgradeTown, QVector <train> Trains, int home_idx)
{
    QJsonArray arrayOfTrains;
    QJsonArray arrayOfTown;
    QJsonObject upgradeObj;
    for(int i = 0; i < Trains.size(); i++)
        arrayOfTrains.push_back(Trains[i].idx);
    if(upgradeTown)
        arrayOfTown.push_back(home_idx);
    upgradeObj.insert("posts", arrayOfTown);
    upgradeObj.insert("trains", arrayOfTrains);
    SendMessageWOW(UPGRADE, upgradeObj);
}

void SocketTest::Finished() {
    emit TurnFinished();
}

void SocketTest::dataArrived() {
    QObject::disconnect(socket,SIGNAL(readyRead()),this,SLOT(dataArrived()));
    QTimer::singleShot(200,this,SLOT(Finished()));
}
