#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "View/mainwindow.h"
#include "edge.h"
#include "strategy.h"
#include "isocketservice.h"
//#include <stdlib.h>
#include <QObject>
#include <QTimeLine>

class GameLogic : public QObject
{
    Q_OBJECT
public:
      GameLogic(ISocketService *service, QVector<Edge *> &edgeVec, Map0 &layer0, Map1 &layer1, Player &player);
      //void gameLoop(DijkstrasAlg *alg);
      ~GameLogic(){}
      void setTrainOnRoute(SocketTest *socket,train playerTrain,QVector<int> &pathToMarket,QVector<QVector<int>> &Table);
      void Alhoritm();
      void trainOneStep(train Train);
      bool CanTrainGo(train Train);
      void animEnemyTrains();
      void animPlayerTrains();
      train CalculateTrainPosition(train Enemy);
      void syncWithServer(train Train);

public slots:
      void trainsOneStep();
private:
      Map0 layer0;
      Map1 layer1;
      Player player;

      ISocketService *service;
      QVector<Edge *> edgeVec;
      train playerTrain;

      QVector <QVector <int>> Table;
      QVector<int> curRoute;
      QVector<int> pointsOfGraph;
      QTimer* time;
      Strategy *strategy;
      QJsonDocument prevMap;
      QTimeLine *animTimer;
      int home_line;
      int home_position;
      int tickTimer;
      //int destDiff;
};
#endif // GAMELOGIC_H
