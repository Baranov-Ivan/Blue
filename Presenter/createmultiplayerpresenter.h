#ifndef CREATEMULTIPLAYERPRESENTER_H
#define CREATEMULTIPLAYERPRESENTER_H

#include <QObject>
#include "View/mainwindow.h"
#include "Model/isocketservice.h"
#include "Model/istarter.h"
#include "Render/graphwidget.h"
#include "View/askselect.h"

class CreateMultiplayerPresenter:public QObject
{
    Q_OBJECT
public:
    explicit CreateMultiplayerPresenter(MainWindow *parent, ISocketService *service);
    virtual ~CreateMultiplayerPresenter();
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
};

#endif // CREATEMULTIPLAYERPRESENTER_H
