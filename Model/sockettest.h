#ifndef SOCKETTEST_H
#define SOCKETTEST_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDataStream>
#include "Collections.h"
#include "structs.h"
class SocketTest : public QObject
{
    Q_OBJECT
public:
    explicit SocketTest(QObject *parent = nullptr);
//    void Connect();
    void SendMessage(Actions Action, QJsonObject jsonData);
    void SendMessageWOW(Actions Action, QJsonObject jsonData);
    QJsonDocument getterDoc();
    void sendMoveMessage(int line_idx, int speed, int train_idx);
    void sendTurnMessage();
    void sendUpgradeMessage(bool upgradeTown, QVector <train> Trains, int home_idx);
    void Connect();
    void sendMap1Message();
    ~SocketTest();
signals:
    void TurnFinished();

public slots:
    void readyRead();
    void disconnect();
    void Finished();
    void dataArrived();    

private:
    QTcpSocket *socket;
    QByteArray Data;
    QJsonDocument doc;
    Result code;
    //QJsonDocument code;
    //QJsonParseError codeError;
    QJsonParseError docError;
    QByteArray toMessageFormat(Actions Action,QJsonObject jsonObj);
};

#endif // SOCKETTEST_H
