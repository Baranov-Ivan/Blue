#ifndef ISOCKETSERVICE_H
#define ISOCKETSERVICE_H

#include <QThread>
#include <QObject>
#include "Model/structs.h"
#include "Model/sockettest.h"

class ISocketService : public QObject
{
    Q_OBJECT
public:
    virtual ~ISocketService(){}
    virtual void OpenConnection() = 0;
    virtual QVector <game> GetGames() = 0;
    virtual void SendMessage(Actions Action, QJsonObject jsonObj) = 0;
    virtual QJsonDocument getDoc() = 0;
    virtual void SendTurnMessage() = 0;
    virtual void SendUpgradeMessage(bool upgradeTown, QVector <train> Trains, int home_idx) = 0;
    virtual void SendMoveMessage(int line_idx, int speed, int train_idx) = 0;
public slots:
    virtual void TurnFinished() = 0;
};

#endif // ISOCKETSERVICE_H
