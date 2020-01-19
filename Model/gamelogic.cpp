#include "gamelogic.h"
#include <QTime>
#include "strategy.h"
GameLogic::GameLogic(ISocketService *service, QVector<Edge *> &edgeVec,Map0 &Layer0, Map1 &Layer1,Player &player)
{
    this->layer0 = Layer0;
    this->layer1 = Layer1;
    this->player = player;

    this->service = service;
    this->edgeVec = edgeVec;
    this->pointsOfGraph = layer0.getterPointsOfgraph();
    this->Table = layer0.getterTable();
    //this->playerTrain = player.getPlayerTrains()[0];
    this->prevMap = {};

    this->home_line = player.getPlayerTrains()[0].line_idx;
    this->home_position = player.getPlayerTrains()[0].position;
    //this->animTimer = new QTimeLine(500);
}

void GameLogic::Alhoritm()
{
    QVector <QVector <int> > Table_sym = Table;
    for(int i = 0; i < Table.size()-1; i++)
    {
        for(int j = i+1; j<Table[i].size();j++)
        {
            Table_sym[i][j] = abs(Table[i][j]);
            Table_sym[j][i] = abs(Table[i][j]);
        }
    }
    int realTownIdx = this->player.getPlayerData().home_idx;
    int townIdx = pointsOfGraph.indexOf(realTownIdx);
    this->strategy = new Strategy(townIdx,Table_sym, pointsOfGraph, layer1.getterPosts(), layer0, service);
    trainsOneStep();
    connect(&*(this->service),SIGNAL(Turn()),this,SLOT(trainsOneStep()));

}

void GameLogic::trainOneStep(train Train) {
        if(this->layer1.checkForCollision(Train.idx)) {
            Train.route.clear();
            Train.postsRoute.clear();
            Train.iter = 1;
            Train.speed = 0;
            Train.position = this->home_position;
            Train.line_idx = this->home_line;
            this->player.setTrainIter(Train.idx,Train.iter);
            this->player.setTrainPosition(Train);
            this->player.setRoute(Train.idx,Train.route);
            this->player.setPostsRoute(Train.idx,Train.postsRoute);
            int homeEdge;
            for(int i = 0; i < edgeVec.size(); i++)
            {
                if(std::abs(edgeVec[i]->getIdx()) == this->home_line)
                {
                    homeEdge = i;
                    break;
                }
            }
            //this->player.getTrain(Train.idx).imageTrain->advancePosition(edgeVec[homeEdge],edgeVec[homeEdge]->getLength(),Train.speed,Train.position,this->animTimer);
            return;
        }
        if(this->layer1.checkForCooldown(Train.idx)) {
                return;
        }

        curRoute = Train.route;
        qDebug() << "ROUTE " << Train.route;
        if(!Train.route.isEmpty()) {
            int sourceEdgePoint = curRoute[Train.iter - 1];
            int destEdgePoint = curRoute[Train.iter];
            int curSpeed = 1;
            int destDiff = 0;
            int curEdgeInfo = Table[std::max(sourceEdgePoint, destEdgePoint)][std::min(sourceEdgePoint, destEdgePoint)];
            int curEdgeIdx = std::abs(curEdgeInfo);
            int curEdge;
            for(int i = 0; i < edgeVec.size(); i++)
            {
                if(std::abs(edgeVec[i]->getIdx()) == curEdgeIdx)
                {
                    curEdge = i;
                    break;
                }
            }
            //Train.line_idx = curEdgeIdx;
            int curLengh = Table[std::min(sourceEdgePoint, destEdgePoint)][std::max(sourceEdgePoint, destEdgePoint)];
            if(Train.iter == 1 && Train.line_idx != curEdgeIdx) {
                Train.line_idx = curEdgeIdx;
                if(sourceEdgePoint < destEdgePoint) {
                    Train.position = 0;
                }
                if(sourceEdgePoint > destEdgePoint) {
                    Train.position = curLengh;
                }
            } else if(Train.line_idx != curEdgeIdx) {
                Train.line_idx = curEdgeIdx;
            }

            if((sourceEdgePoint < destEdgePoint) && (curEdgeInfo > 0)) {
                curSpeed = 1;
                destDiff = 0;
            } else if((sourceEdgePoint > destEdgePoint) && (curEdgeInfo > 0)) {
                curSpeed = -1;
                destDiff = curLengh;
            } else if((sourceEdgePoint < destEdgePoint) && (curEdgeInfo < 0)) {
                curSpeed = -1;
                destDiff = curLengh;
            } else if((sourceEdgePoint > destEdgePoint) && (curEdgeInfo < 0)) {
                curSpeed = 1;
                destDiff = 0;
            }
            Train.speed = curSpeed;
            if(Train.position != (curLengh - destDiff)) {
                service->SendMoveMessage(curEdgeIdx,curSpeed,Train.idx);
                if((curLengh - destDiff) == curLengh) {
                    Train.position++;
                    this->player.setTrainPosition(Train);
                } else if((curLengh - destDiff) == 0){
                    Train.position--;
                    this->player.setTrainPosition(Train);
                }
            } else {
// Разбор стыка рёбер. Не оч красиво, но работает.
                if(Train.iter + 1 < curRoute.size()) {
                    if((curRoute[Train.iter] < curRoute[Train.iter+1]) && (Table[std::max(curRoute[Train.iter], curRoute[Train.iter+1])][std::min(curRoute[Train.iter], curRoute[Train.iter+1])] > 0)) {
                        Train.position = 0;
                        Train.iter++;
                        this->player.setTrainIter(Train.idx,Train.iter);
                        this->player.setTrainPosition(Train);
                        //continue;
                        trainOneStep(Train);
                    } else if ((curRoute[Train.iter] > curRoute[Train.iter+1]) && (Table[std::max(curRoute[Train.iter], curRoute[Train.iter+1])][std::min(curRoute[Train.iter], curRoute[Train.iter+1])] > 0)) {
                        Train.position = Table[std::min(curRoute[Train.iter], curRoute[Train.iter+1])][std::max(curRoute[Train.iter], curRoute[Train.iter+1])];
                        Train.iter++;
                        this->player.setTrainIter(Train.idx,Train.iter);
                        this->player.setTrainPosition(Train);
                        //continue;
                        trainOneStep(Train);
                    } else if ((curRoute[Train.iter] < curRoute[Train.iter+1]) && (Table[std::max(curRoute[Train.iter], curRoute[Train.iter+1])][std::min(curRoute[Train.iter], curRoute[Train.iter+1])] < 0)) {
                        Train.position = Table[std::min(curRoute[Train.iter], curRoute[Train.iter+1])][std::max(curRoute[Train.iter], curRoute[Train.iter+1])];
                        Train.iter++;
                        this->player.setTrainIter(Train.idx,Train.iter);
                        this->player.setTrainPosition(Train);
                        //continue;
                        trainOneStep(Train);
                    } else if ((curRoute[Train.iter] > curRoute[Train.iter+1]) && (Table[std::max(curRoute[Train.iter], curRoute[Train.iter+1])][std::min(curRoute[Train.iter], curRoute[Train.iter+1])] < 0)) {
                        Train.position = 0;
                        Train.iter++;
                        this->player.setTrainIter(Train.idx,Train.iter);
                        this->player.setTrainPosition(Train);
                        //continue;
                        trainOneStep(Train);
                    }
                } else {
                    if(curRoute[Train.iter] == pointsOfGraph.indexOf(player.getPlayerData().home_idx))
                    {
                        Train.route.clear();
                        Train.postsRoute.clear();
                        Train.iter = 1;
                        this->player.setTrainIter(Train.idx,Train.iter);
                        this->player.setTrainPosition(Train);
                        this->player.setRoute(Train.idx, Train.route);
                        this->player.setPostsRoute(Train.idx, Train.postsRoute);

                    } else if (curRoute[Train.iter] == Train.route.last()) {
                        qDebug() << Train.position;
                        Train.route.clear();
                        this->player.setRoute(Train.idx, Train.route);
                        this->player.setWaitIteration(Train.idx, 0);
                        this->strategy->Moving(this->layer1, this->player);
                        Train.iter = 1;
                        this->player.setTrainIter(Train.idx,Train.iter);
                        this->player.setTrainPosition(Train);
                        Train.route = player.getTrain(Train.idx).route;
                        trainOneStep(Train);
                    }
                }
          }
    } else {
            qDebug() << "ROUTE IS EMPTY!!!!!!!";
        }
}

void GameLogic::trainsOneStep()
{
    //this->animTimer = nullptr;
    service->SendMessage(MAP,{{"layer",1}});
    this->layer1.Pars(service->getDoc());

    if(this->layer1.checkForGameOver(this->player.getPlayerIdx())) {
        qDebug() << "GAME OVER";
    }

    this->animTimer = new QTimeLine(200);
    this->strategy->Moving(this->layer1, this->player);
    for(int i = 0; i < this->player.getPlayerTrains().size(); i++)
    {
        syncWithServer(this->layer1.getPlayerTrain(this->player.getPlayerData().player_idx,this->player.getPlayerTrains()[i].idx));
        trainOneStep(this->player.getPlayerTrains()[i]);
    }
    animPlayerTrains();
    if(player.getEnemies().size() > 0)
    {
        animEnemyTrains();
    }
    this->animTimer->start();
    service->SendTurnMessage();
}

void GameLogic::animEnemyTrains()
{
   for(int i = 0; i < this->player.getEnemies().size(); i++)
   {
        for(int j = 0; j < this->player.getEnemies()[i].trains.size(); j++)
        {
            int train_idx = player.getEnemies()[i].trains[j].idx;

            train enemyTrain = this->layer1.getEnemyTrain(player.getEnemies()[i].player_idx,train_idx);
            int curEdge = -1;
            int curLength = -1;
            for(int z = 0; z < edgeVec.size(); z++)
            {
                if(std::abs(edgeVec[z]->getIdx()) == enemyTrain.line_idx)
                {
                    curEdge = z;
                    curLength = edgeVec[z]->getLength();
                    break;
                }
            }
            this->player.getEnemies()[i].trains[j].imageTrain->advancePosition(edgeVec[curEdge],curLength,enemyTrain.speed,enemyTrain.position,this->animTimer);
        }
   }

}

/*bool GameLogic::CanTrainGo(train Train)
{
    Train = CalculateTrainPosition(Train);
    QPair <int, int> pairOfPoints = layer0.getPoints(Train.line_idx);
    for(int i = 0; i < layer1.getTrains().size(); i++)
    {
        train enemyTrain = CalculateTrainPosition(layer1.getTrains()[i]);
        if(((enemyTrain.position == Train.position && enemyTrain.line_idx == Train.line_idx)||(enemyTrain.killer == true)) &&
            (std::min(pointsOfGraph[pairOfPoints.first], pointsOfGraph[pairOfPoints.second]) != player.getPlayerData().home_idx))
            return false;
    }
    return true;
}

train GameLogic::CalculateTrainPosition(train Train)
{
    QPair <int, int> pairOfPoints = layer0.getPoints(Train.line_idx);
    int curLength = Table[std::min(pairOfPoints.first, pairOfPoints.second)][std::max(pairOfPoints.first, pairOfPoints.second)];
    int speedInfo = Table[std::max(pairOfPoints.first, pairOfPoints.second)][std::min(pairOfPoints.first, pairOfPoints.second)];
    train newTrain = Train;
    if(Train.position == 0 || Train.position == curLength)
    {
        if(std::min(pointsOfGraph[pairOfPoints.first], pointsOfGraph[pairOfPoints.second]) != player.getPlayerData().home_idx)
            newTrain.killer = true;
    } else {
        if(Train.speed == 0)
        {}
        else if((speedInfo < 0 && Train.speed < 0) || (speedInfo > 0 && Train.speed > 0))
            newTrain.position++;
        else
            newTrain.position--;
    }
    return newTrain;
}*/

void GameLogic::animPlayerTrains() {
    for(int i = 0; i < this->player.getPlayerTrains().size(); i++)
    {
        int train_idx = player.getPlayerTrains()[i].idx;

        train playerTrain = this->layer1.getPlayerTrain(player.getPlayerData().player_idx,train_idx);
        int curEdge = -1;
        int curLength = -1;
        for(int j = 0; j < edgeVec.size(); j++)
        {
            if(std::abs(edgeVec[j]->getIdx()) == playerTrain.line_idx)
            {
                curEdge = j;
                curLength = edgeVec[j]->getLength();
                break;
            }
        }
        this->player.getPlayerTrains()[i].imageTrain->advancePosition(edgeVec[curEdge],curLength,playerTrain.speed,playerTrain.position,this->animTimer);
    }
}

void GameLogic::syncWithServer(train Train)
{

    if(this->player.getTrain(Train.idx).position != Train.position)
    {
        this->player.setTrainPosition(Train);
    }

}
