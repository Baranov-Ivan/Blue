#ifndef SINGLEPLAYERPRESENTER_H
#define SINGLEPLAYERPRESENTER_H

#include <QObject>
#include "View/mainwindow.h"
#include "Model/isocketservice.h"
#include "Model/socketservice.h"
#include "View/askselect.h"
#include "View/mainwindowforsingleplay.h"
#include "Render/graphwidget.h"
#include "Model/istarter.h"
#include "Model/starter.h"

class SinglePlayerPresenter:public QObject
{
    Q_OBJECT
public:
    explicit SinglePlayerPresenter(MainWindow *parent, ISocketService * service);
    ~SinglePlayerPresenter();
private:
    MainWindow *parent;
    ISocketService * service;
    IStarter *starter;
    Player player;
    Map0 layer0;
public slots:
    void LoginPush();
    void BackPush();
    void StartStarter(QVector<Edge *> edgeVec, Player& player);
};
#endif // SINGLEPLAYERPRESENTER_H
