#include "structs.h"
#include "QDebug"

void Map0::Pars(QJsonDocument doc)
{
    qDebug() << doc;
    QJsonObject jsonObject = doc.object();
    QJsonArray jsonArray = jsonObject["points"].toArray();
    foreach(const QJsonValue & value, jsonArray)
    {
        QJsonObject obj = value.toObject();
        this->pointsOfGraph.append(obj["idx"].toInt());
    }
    jsonArray = jsonObject["lines"].toArray();
    QVector <QVector <int> > Layer0(pointsOfGraph.size(), QVector <int> (pointsOfGraph.size()));
    this->Table = Layer0;
    Layer0.clear();
    foreach(const QJsonValue & value, jsonArray)
    {
        QJsonObject obj = value.toObject();
        int i = (obj["points"].toArray())[0].toInt();
        int j = (obj["points"].toArray())[1].toInt();
        for(int i1 = 0; i1 < this->pointsOfGraph.size(); i1++)
        {
            if(i == this->pointsOfGraph[i1])
            {
                i = i1;
            }
            if(j == this->pointsOfGraph[i1])
            {
                j = i1;
            }
        }

        //3rd
        if(i < j) {
            this->Table[i][j] = obj["length"].toInt();
            this->Table[j][i] = obj["idx"].toInt();
        } else {
            this->Table[j][i] = obj["length"].toInt();
            this->Table[i][j] = obj["idx"].toInt()*(-1);
        }
    }
}
QVector <int> Map0::getterPointsOfgraph()
{
    return pointsOfGraph;
}
QVector <QVector <int> > Map0::getterTable()
{
    return Table;
}

void Map1::Pars(QJsonDocument doc)
{
    QJsonObject jsonObject = doc.object();
    QJsonArray jsonArray = jsonObject["posts"].toArray();
    Posts.clear();
    Towns.clear();
    Markets.clear();
    Storages.clear();
    AllTrains.clear();
    foreach(const QJsonValue & value, jsonArray)
    {
        QJsonObject obj = value.toObject();
        post Post;
        Post.point_idx = obj["point_idx"].toInt();
        Post.idx = obj["idx"].toInt();
        Post.type = obj["type"].toInt();
        this->Posts.append(Post);
        if(obj["type"] == TOWN)
        {
            town Town;
            Town.population = obj["population"].toInt();
            Town.products = obj["product"].toInt();
            Town.armor = obj["armor"].toInt();
            Town.level = obj["level"].toInt();
            Town.price = obj["next_level_price"].toInt();
            Town.idx = Post.idx;
            Town.name = obj["name"].toString();
            Town.point_idx = Post.point_idx;
            Town.player_idx = obj["player_idx"].toString();
            Town.armor_capacity = obj["armor_capacity"].toInt();
            Town.products_capacity = obj["products_capacity"].toInt();
            Town.population_capacity = obj["population_capacity"].toInt();
            QJsonArray eventsArray = obj["events"].toArray();
            foreach(const QJsonValue & value, eventsArray) {
                QJsonObject obj = value.toObject();
                if(obj["type"] == GAME_OVER) {
                    Town.game_over = true;
                }
            }
            this->Towns.append(Town);
        }
        if(obj["type"].toInt() == MARKET) {
            market Market;
            Market.idx = obj["idx"].toInt();
            Market.point_idx = obj["point_idx"].toInt();
            Market.goods = obj["product"].toInt();
            Market.goods_capacity = obj["product_capacity"].toInt();
            Market.replenishment = obj["replenishment"].toInt();
            Market.type = obj["type"].toInt();
            Market.name = obj["name"].isString();
            Market.mark = 0;
            this->Markets.append(Market);
        }
        if(obj["type"].toInt() == STORAGE) {
            market Storage;
            Storage.idx = obj["idx"].toInt();
            Storage.point_idx = obj["point_idx"].toInt();
            Storage.goods = obj["armor"].toInt();
            Storage.goods_capacity = obj["armor_capacity"].toInt();
            Storage.replenishment = obj["replenishment"].toInt();
            Storage.type = obj["type"].toInt();
            Storage.name = obj["name"].isString();
            Storage.mark = 0;
            this->Storages.append(Storage);
        }

    }
    jsonArray = jsonObject["trains"].toArray();
    foreach(const QJsonValue & value, jsonArray) {
        QJsonObject obj = value.toObject();
        train Train;
        Train.player_idx = obj["player_idx"].toString();
        Train.idx = obj["idx"].toInt();
        Train.goods = obj["goods"].toInt();
        Train.goods_capacity = obj["goods_capacity"].toInt();
        Train.goods_type = static_cast<GoodsType>(obj["goods_type"].toInt());
        Train.line_idx = obj["line_idx"].toInt();
        Train.position = obj["position"].toInt();
        Train.speed = obj["speed"].toInt();
        Train.level = obj["level"].toInt();
        Train.price = obj["next_level_price"].toInt();
        Train.cooldown = obj["cooldown"].toInt();
        QJsonArray eventsArray = obj["events"].toArray();
        qDebug()<<"EVENTS ARRAY:"<<eventsArray;
        //qDebug()<<"SAAAAAAAAAIIIIIZZZZZZZZZEEEEEE"<<eventsArray.size();
        if(eventsArray.size() != 0) {
            Train.collisionEvent = 1;
        } else {
            Train.collisionEvent = 0;
        }
        this->AllTrains.append(Train);
    }

}

void Map10::Pars(QJsonDocument doc)
{
    QJsonObject jsonObject = doc.object();
    QJsonArray jsonArray = jsonObject["coordinates"].toArray();
    foreach(const QJsonValue & value, jsonArray)
    {
        QJsonObject obj = value.toObject();
        int idx = obj["idx"].toInt();
        point Point;
        Point.x = obj["x"].toInt();
        Point.y = obj["y"].toInt();
        this->coords.append(QPair<int,point>(idx,Point));
    }
    this->idx = jsonObject["idx"].toInt();
    jsonArray = jsonObject["size"].toArray();
    this->size_x = jsonArray[0].toInt();
    this->size_y = jsonArray[1].toInt();
}

int Map10::getSizeX()
{
    return this->size_x;
}

int Map10::getSizeY()
{
    return this->size_y;
}

point Map10::getCoordsByIdx(int idx)
{
    for(int i = 0; i < this->coords.size(); i++)
    {
        if(coords[i].first == idx)
        {
            return coords[i].second;
        }
    }
}

QVector <post> Map1::getterPosts()
{
    return this->Posts;
}

QVector <market> Map1::getterMarkets()
{
    return this->Markets;
}

QVector <market> Map1::getterStorages()
{
    return this->Storages;
}
void Player::Pars(QJsonDocument doc) {
    QJsonObject jsonObject = doc.object();
    QJsonObject jsonHomeObject = jsonObject["home"].toObject();
    this->playerData.home_idx = jsonHomeObject["idx"].toInt();
    this->playerData.home_post_idx = jsonHomeObject["post_idx"].toInt();

    this->playerData.in_game = jsonObject["in_game"].toBool();
    this->playerData.name = jsonObject["name"].toString();
    this->playerData.rating = jsonObject["rating"].toInt();
    this->playerData.player_idx = jsonObject["idx"].toString();

    QJsonArray jsonArray = jsonObject["trains"].toArray();
    foreach(const QJsonValue & value, jsonArray) {
        QJsonObject obj = value.toObject();
        train Train;
        Train.player_idx = obj["player_idx"].toString();
        Train.idx = obj["idx"].toInt();
        Train.goods = obj["goods"].toInt();
        Train.goods_capacity = obj["goods_capacity"].toInt();
        Train.goods_type = static_cast<GoodsType>(obj["goods_type"].toInt());
        Train.line_idx = obj["line_idx"].toInt();
        this->playerData.home_line_idx = Train.line_idx;
        Train.position = obj["position"].toInt();
        Train.speed = obj["speed"].toInt();
        Train.level = obj["level"].toInt();
        Train.price = obj["next_level_price"].toInt();
        Train.waitIteration = 0;
        this->playerTrains.append(Train);
    }
}

player Player::getPlayerData()
{
    return playerData;
}

QVector<train> Player::getPlayerTrains() {
    return playerTrains;
}

void Player::setTrainsLevel(QVector <train> Trains)
{
    for(int i = 0; i < Trains.size(); i++)
    {
        for(int j = 0; j < this->playerTrains.size(); j++)
        {
            if(Trains[i].idx == this->playerTrains[j].idx)
            {
                this->playerTrains[j].level = Trains[i].level;
            }
        }
    }
}

int Map1::getTick() {
    return this->tick;
}

QVector <train> Map1::getTrains()
{
    return this->AllTrains;
}

town Map1::getHome(QString player_idx)
{
    for(int i = 0; i < Towns.size(); i++)
    {
        if(Towns[i].player_idx == player_idx)
            return Towns[i];
    }
}

QVector <game> ExistingGames::getGames()
{
    return this->games;
}

void ExistingGames::Pars(QJsonDocument doc)
{
    QJsonObject jsonObject = doc.object();
    QJsonArray jsonArray = jsonObject["games"].toArray();
    foreach(const QJsonValue & value, jsonArray)
    {
        QJsonObject obj = value.toObject();
        game Game;
        Game.gameName = obj["name"].toString();
        Game.gameState = static_cast<GameState>(obj["state"].toInt());
        Game.numberOfTurns = obj["num_turns"].toInt();
        Game.numberOfPlayers = obj["num_players"].toInt();
        this->games.append(Game);
    }
}

void Player::ParsEnemies(Map1 layer1)
{
    QVector <town> Towns = layer1.getTown();
    QVector <train> Trains = layer1.getTrains();
    Enemies.clear();
    for(int i = 0; i < Towns.size(); i++)
    {
        enemy Enemy;
        if(Towns[i].player_idx != playerData.player_idx && Towns[i].player_idx != "")
        {
            Enemy.Town = Towns[i];
            for(int j = 0; j < layer1.getTrains().size(); j++)
            {
                if(Trains[j].player_idx == Towns[i].player_idx)
                    Enemy.trains.append(Trains[j]);
            }
            Enemy.player_idx = Enemy.Town.player_idx;
            Enemies.append(Enemy);
        }
    }
}

QVector <train> Map1::getAllEnemiesTrains(QString player_idx)
{
    QVector <train> Trains;
    for(int i = 0; i < AllTrains.size(); i++)
    {
        if(AllTrains[i].player_idx != player_idx)
            Trains.append(AllTrains[i]);
    }
    return Trains;
}

train Map1::getEnemyTrain(QString enemy_idx, int train_idx)
{
    for(int i = 0; i < AllTrains.size(); i++)
    {
        if(AllTrains[i].idx == train_idx){
            return AllTrains[i];
        }
    }
}

train Map1::getPlayerTrain(QString player_idx, int train_idx)
{
    for(int i = 0; i < AllTrains.size(); i++)
    {
        if(AllTrains[i].idx == train_idx){
            return AllTrains[i];
        }
    }
}

QVector <town> Map1::getTown()
{
    return Towns;
}

QVector <enemy> Player::getEnemies()
{
    return Enemies;
}

QVector <town> Player::getEnemiesTown()
{
    QVector <town> Towns;
    for(int i = 0; i < Enemies.size(); i++)
        Towns.append(Enemies[i].Town);
    return Towns;
}

void Player::setRoute(int train_idx, QVector<int> route)
{
    for(int i = 0; i < playerTrains.size(); i++)
    {
        if(playerTrains[i].idx == train_idx)
        {
            playerTrains[i].route = route;
            break;
        }
    }
}

void Player::setPostsRoute(int train_idx, QVector<int> route)
{
    for(int i = 0; i < playerTrains.size(); i++)
    {
        if(playerTrains[i].idx == train_idx)
        {
            playerTrains[i].postsRoute = route;
            break;
        }
    }
}

void Player::setWaitIteration(int train_idx, int iter)
{
    for(int i = 0; i < playerTrains.size(); i++)
    {
        if(playerTrains[i].idx == train_idx)
        {
            playerTrains[i].waitIteration = iter;
            break;
        }
    }
}

void Player::setTrainPosition(train Train)
{
    for(int i = 0; i < playerTrains.size(); i++)
    {
        if(playerTrains[i].idx == Train.idx)
        {
            playerTrains[i].speed = Train.speed;
            playerTrains[i].line_idx = Train.line_idx;
            playerTrains[i].position = Train.position;
            break;
        }
    }
}

void Player::setTrainIter(int idx,int iter)
{
    for(int i = 0; i < playerTrains.size(); i++)
    {
        if(playerTrains[i].idx == idx)
        {
            playerTrains[i].iter = iter;
            break;
        }
    }
}

void Player::setTrainImage(Train *trainImage, int index)
{
    this->playerTrains[index].imageTrain = trainImage;
}

void Player::setEnemyTrainImage(Train *trainImage, QString enemy_idx,int train_idx)
{
    for(int i = 0; i < Enemies.size(); i++)
    {
        if(Enemies[i].player_idx == enemy_idx)
        {
            for(int j = 0; j < Enemies[i].trains.size(); j++)
            {
                if(Enemies[i].trains[j].idx == train_idx)
                {
                    this->Enemies[i].trains[j].imageTrain = trainImage;
                    break;
                }
            }
        }

    }
}

train Player::getTrain(int idx)
{
    for(int i = 0; i < playerTrains.size(); i++)
    {
        if(idx == playerTrains[i].idx)
        {
            return this->playerTrains[i];
        }
    }
}

train Map1::getTrain(int idx)
{
    for(int i = 0; i < AllTrains.size(); i++)
    {
        if(idx == AllTrains[i].idx)
        {
            return this->AllTrains[i];
        }
    }
}

bool Map1::checkForCollision(int idx){
    if(this->getTrain(idx).collisionEvent == 0) {
        return false;
    } else {
        return true;
    }
}

bool Map1::checkForCooldown(int idx){
    if(this->getTrain(idx).cooldown == 0) {
        return false;
    } else {
        return true;
    }
}

bool Map1::checkForGameOver(QString player_idx) {
    if(this->getHome(player_idx).game_over) {
        return true;
    } else {
        return false;
    }
}

void Player::setPointsToAvoid(train Train, QVector<int> pointsToAvoid)
{
    playerTrains[playerTrains.indexOf(Train)].pointsToAvoid = pointsToAvoid;
}

bool train::operator==(const train &anotherTrain)
{
    if(this->idx == anotherTrain.idx)
        return true;
    else
        return false;
}

bool player::operator==(player &anotherPlayer)
{
    if(this->player_idx == anotherPlayer.player_idx)
        return true;
    else
        return false;
}

QPair <int, int> Map0::getPoints(int line_idx)
{
    for(int i = 0; i < this->pointsOfGraph.size(); i++)
    {
        for(int j = 0; j < this->pointsOfGraph.size(); j++)
        {
            if(Table[i][j] == line_idx)
                return qMakePair(i, j);
        }
    }
}

QString Player::getPlayerIdx() {
    return this->playerData.player_idx;
}
