#include "createmultiplayerpresenter.h"

CreateMultiplayerPresenter::CreateMultiplayerPresenter(MainWindow *parent, ISocketService *service)
{
    this->parent = parent;
    this->service = service;
    connect(&*(this->parent), SIGNAL(StartGame()), this, SLOT(LoginPush()));
    connect(&*(this->parent), SIGNAL(BackPush()), this, SLOT(BackPush()));
}

CreateMultiplayerPresenter::~CreateMultiplayerPresenter()
{}

void CreateMultiplayerPresenter::LoginPush()
{
    service->OpenConnection();
    service->SendMessage(LOGIN, parent->getLoginData());
    player.Pars(service->getDoc());

    service->SendMessage(MAP,{{"layer", 0}});
    layer0.Pars(service->getDoc());

    service->SendMessage(MAP,{{"layer", 1}});
    Map1 layer1;
    layer1.Pars(service->getDoc());
    player.ParsEnemies(layer1);

    service->SendMessage(MAP,{{"layer", 10}});
    Map10 layer10;
    layer10.Pars(service->getDoc());

    widget = new GraphWidget(nullptr, parent, player, layer0, layer1, layer10);
    connect(&*(widget), SIGNAL(RenderFinished(QVector<Edge *>, Player&)), &*(this), SLOT(StartStarter(QVector <Edge *>, Player&)));
    widget->Render();
}

void CreateMultiplayerPresenter::BackPush()
{
    AskSelect *window = new AskSelect();
}
void CreateMultiplayerPresenter::StartStarter(QVector<Edge *> edgeVec, Player& player)
{
    this->player = player;
    starter = new Starter(service, parent->getGame(), player, layer0, edgeVec);
    connect(&*(starter),SIGNAL(SetEnemyTrains(enemy, Player&)),&*(widget),SLOT(SetEnemyTrains(enemy, Player&)));
    connect(&*(starter),SIGNAL(Update(town )),&*(widget),SLOT(Update(town )));
    starter->CheckAndStart();
}
