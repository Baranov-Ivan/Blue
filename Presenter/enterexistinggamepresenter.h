#ifndef ENTEREXISTINGGAMEPRESENTER_H
#define ENTEREXISTINGGAMEPRESENTER_H

#include "View/mainwindow.h"
#include "Model/isocketservice.h"
#include "Model/istarter.h"
#include "View/askselect.h"
#include <QObject>

class EnterExistingGamePresenter:public QObject
{
    Q_OBJECT
public:
    explicit EnterExistingGamePresenter(MainWindow *parent, ISocketService *service);
    virtual ~EnterExistingGamePresenter();
private:
    MainWindow *parent;
    ISocketService * service;
    IStarter *starter;
    Player player;
    Map0 layer0;
    GraphWidget *widget;
public slots:
    void LoginPush();
    void BackPush();
    void StartStarter(QVector<Edge *> edgeVec, Player& player);
    void AskExistingGames();
signals:
    void ShowGames(ExistingGames games);
};

#endif // ENTEREXISTINGGAMEPRESENTER_H
