#ifndef SOCKETSERVICE_H
#define SOCKETSERVICE_H

#include "Model/isocketservice.h"

class SocketService :public ISocketService
{
    Q_OBJECT
public:
    SocketService();
    void OpenConnection() override;
    void SendMessage(Actions Action, QJsonObject jsonObj) override;
    QVector<game> GetGames() override;
    QJsonDocument getDoc() override;
    void SendTurnMessage() override;
    void SendUpgradeMessage(bool upgradeTown, QVector<train> Trains, int home_idx) override;
    void SendMoveMessage(int line_idx, int speed, int train_idx) override;
private:
    SocketTest *socket;
public slots:
    void TurnFinished() override;
signals:
    void Turn();
};

#endif // SOCKETSERVICE_H
