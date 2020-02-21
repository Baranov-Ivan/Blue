#include "socketservice.h"

SocketService::SocketService()
{
    this->socket = new SocketTest(nullptr);
    connect(&*(this->socket), SIGNAL(TurnFinished()), this, SLOT(TurnFinished()));
}

void SocketService::OpenConnection()
{
    this->socket->Connect();
}

QVector <game> SocketService::GetGames()
{
    this->socket->SendMessage(GAMES,{});
    ExistingGames games;
    games.Pars(this->socket->getterDoc());
    QVector <game> gameList;
    gameList = games.getGames();
    return gameList;
}

void SocketService::SendMessage(Actions Action, QJsonObject jsonObj)
{
    this->socket->SendMessage(Action, jsonObj);
}

QJsonDocument SocketService::getDoc()
{
    return socket->getterDoc();
}

void SocketService::TurnFinished()
{
    emit Turn();
}

void SocketService::SendTurnMessage()
{
    this->socket->sendTurnMessage();
}

void SocketService::SendUpgradeMessage(bool upgradeTown, QVector<train> Trains, int home_idx)
{
    this->socket->sendUpgradeMessage(upgradeTown, Trains, home_idx);
}

void SocketService::SendMoveMessage(int line_idx, int speed, int train_idx)
{
    this->socket->sendMoveMessage(line_idx, speed, train_idx);
}
