#ifndef STARTER_H
#define STARTER_H

#include "istarter.h"
#include "gamelogic.h"

class Starter : public IStarter
{
    Q_OBJECT
public:
    Starter(ISocketService *service, game *currentGame, Player &player, Map0 layer0, QVector<Edge *> edgeVec);
    void StartGameLogic() override;
public slots:
    void CheckAndStart() override;
    void Check() override;
private:
    QTimer *timer;
    ISocketService *service;
    game *currentGame;
    Player player;
    Map1 layer1;
    Map0 layer0;
    QVector<Edge *> edgeVec;
signals:
    void Update(town Town);
    void SetEnemyTrains(enemy Enemy,Player& player);
};

#endif // STARTER_H
