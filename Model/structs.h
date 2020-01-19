#ifndef STRUCTS_H
#define STRUCTS_H
#include <QVector>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "Collections.h"
#include "train.h"

struct point
{
    int x;
    int y;
};

struct town
{
    int idx;
    int armor;
    int armor_capacity;
    int products;
    int products_capacity;
    QString name;
    QString player_idx;
    int point_idx;
    int population;
    int population_capacity;
    int level;
    int price;
    bool game_over = false;
};

struct player
{
    QString idx;
    bool in_game;
    QString name;
    int rating;
    int home_idx;
    int home_post_idx;
    QString player_idx;
    int home_line_idx;
    bool operator==(player &anotherPlayer);
};

struct train
{
    QString player_idx;
    int idx;
    int goods;
    int goods_capacity;
    GoodsType goods_type;
    int line_idx;
    int position;
    int speed;
    int level;
    int price;
    int cooldown;
    int collisionEvent;
    QVector <int> route;
    QVector <int> postsRoute;
    QVector <int> pointsToAvoid;
    int waitIteration;
    int iter = 1;
    Train* imageTrain;
    bool operator==(const train &anotherTrain);
};


struct post
{
  int idx;
  int point_idx;
  int type;
};

struct market
{
  QString name;
  int idx;
  int point_idx;
  int goods;
  int goods_capacity;
  int replenishment;
  int type;
  int mark;
};

struct game
{
    QString gameName;
    int numberOfPlayers;
    int numberOfTurns;
    GameState gameState;
};

struct enemy:player
{
    town Town;
    QVector <train> trains;
};

class Map0 //если будет нужно позже я добавлю те пункты, пока что их предназначение в это мире не ясно
{
private:
    QVector <int> pointsOfGraph;
    QVector <QVector <int> > Table;
public:
    Map0(){}
    ~Map0(){}
    void Pars(QJsonDocument doc);
    QVector <int> getterPointsOfgraph();
    QVector <QVector <int> > getterTable();
    QPair <int, int> getPoints(int line_idx);
};

class Map10
{
private:
    QVector<QPair<int,point>> coords;
    int size_x;
    int size_y;
    int idx;
public:
    Map10(){}
    ~Map10(){}
    void Pars(QJsonDocument doc);
    int getSizeX();
    int getSizeY();
    point getCoordsByIdx(int idx);
};

class Map1
{
private:
    QVector <post> Posts;
    QVector <market> Markets;
    QVector <market> Storages;
    QVector <town> Towns;
    QVector <train> AllTrains;
    int tick;
    int population;
    int products;
    int armor;
    int level;
    int price;
public:
    Map1(){}
    void Pars(QJsonDocument doc);
    QVector <post> getterPosts();
    QVector <market> getterMarkets();
    QVector <market> getterStorages();
    int getTick();
    QVector <train> getTrains();
    QVector <town> getTown();
    QVector <train> getAllEnemiesTrains(QString player_idx);
    train getEnemyTrain(QString enemy_idx, int train_idx);
    train getPlayerTrain(QString player_idx, int train_idx);
    town getHome(QString player_idx);
    train getTrain(int idx);
    bool checkForCollision(int idx);
    bool checkForCooldown(int idx);
    bool checkForGameOver(QString player_idx);
    ~Map1(){}
};

class Player
{
private:
    player playerData;
    QVector<train> playerTrains;
    QVector <enemy> Enemies;
public:
    Player(){}
    ~Player(){}
    void Pars(QJsonDocument doc);
    player getPlayerData();
    QVector <train> getPlayerTrains();
    void setTrainsLevel(QVector <train> Trains);
    void ParsEnemies(Map1 layer1);
    QVector <enemy> getEnemies();
    QVector <town> getEnemiesTown();
    void setRoute(int train_idx, QVector <int> route);
    void setPostsRoute(int train_idx, QVector <int> route);
    void setWaitIteration(int train_idx, int iter);
    void setTrainImage(Train* trainImage,int index);
    train getTrain(int idx);
    void setTrainPosition(train Train);
    void setTrainIter(int idx,int iter);
    void setPointsToAvoid(train Train, QVector<int> pointsToAvoid);
    void setKiller(train Train, bool IsKiller);
    void setEnemyTrainImage(Train* trainImage, QString enemy_idx,int train_idx);
    QString getPlayerIdx();
};

class ExistingGames
{
private:
    QVector <game> games;
public:
    ExistingGames(){}
    ~ExistingGames(){}
    void Pars(QJsonDocument doc);
    QVector <game> getGames();
};

#endif // STRUCTS_H
