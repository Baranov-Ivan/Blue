#include "starter.h"

Starter::Starter(ISocketService *service, game *currentGame, Player &player, Map0 layer0, QVector <Edge *> edgeVec)
{
    this->service = service;
    this->currentGame = currentGame;
    this->player = player;
    this->layer0 = layer0;
    this->edgeVec = edgeVec;
}

void Starter::CheckAndStart()
{
    this->timer = new QTimer(nullptr);
    connect(&*(timer), SIGNAL(timeout()), this, SLOT(Check()));
    this->timer->start(1000);

}

void Starter::Check()
{
    service->SendMessage(GAMES,{});
    ExistingGames games;
    games.Pars(service->getDoc());
    QVector <game> Games = games.getGames();
    game ourGame;
    for(int i = 0; i < Games.size(); i++)
    {
        if(Games[i].gameName == this->currentGame->gameName)
        {
            ourGame = Games[i];
            break;
        }
    }
    if(ourGame.gameState == RUN) {
        service->SendMessage(MAP,{{"layer", 1}});
        Map1 layer1;
        layer1.Pars(service->getDoc());
        this->layer1 = layer1;
        QVector <enemy> Enemies = player.getEnemies();
        player.ParsEnemies(layer1);
        if(Enemies.size() != this->player.getEnemies().size())
        {
            for(int i = 0; i < this->player.getEnemiesTown().size(); i++)
            {
                emit Update(player.getEnemiesTown()[i]);
            }
        }
        for(int i = 0; i < this->player.getEnemies().size(); i++)
        {
            emit SetEnemyTrains(this->player.getEnemies()[i],this->player);
        }
        this->StartGameLogic();
        timer->stop();
    }
}

void Starter::StartGameLogic()
{
    GameLogic *alg = new GameLogic(service,this->edgeVec, this->layer0,this->layer1,this->player);
    alg->Alhoritm();
}
