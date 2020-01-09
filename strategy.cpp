#include "strategy.h"
#include "dijkstrasalg.h"
#include "dijkstrasalg.cpp"
Strategy::Strategy(int townIdx,QVector <QVector <int> > &Table, QVector<int> &pointsOfGraph, QVector<post> posts, SocketTest *socket):alg(townIdx, Table, pointsOfGraph, posts)
{
    this->pointsOfGraph = pointsOfGraph;
    this->shortestPaths = alg.getPaths();
    this->socket = socket;
}

void Strategy::Moving(Map1 &map, Player &player)
{
    this->shortestPaths = alg.getPaths();
    QVector <market> markets = map.getterMarkets();
    QVector <market> storages = map.getterStorages();
    QVector <train> upgradeTrains;
    QVector <market> GoodMarkets = GoodPosts(map, markets, player);
    QVector <int> pointsToVisit(0);
    QVector <int> pointsToAvoid(0);

    if(player.getEnemies().size() == 0)
    {

        int currentArmor = map.getHome(player.getPlayerData().player_idx).armor;
        if(map.getHome(player.getPlayerData().player_idx).level < player.getPlayerTrains()[player.getPlayerTrains().size() - 1].level &&
                map.getHome(player.getPlayerData().player_idx).price <= currentArmor)
        {
            currentArmor -= map.getHome(player.getPlayerData().player_idx).price;
            if(currentArmor > player.getPlayerTrains()[player.getPlayerTrains().size() - 1].price && player.getPlayerTrains()[player.getPlayerTrains().size() - 1].price != 0)
            {
                int start = 0;
                for(int i = 0; i < player.getPlayerTrains().size() - 1; i++)
                {
                    if(player.getPlayerTrains()[i].level > player.getPlayerTrains()[i + 1].level)
                    {
                        start = i + 1;
                        break;
                    }
                }
                for(int i = start; i < player.getPlayerTrains().size(); i++)
                {
                    if(currentArmor > player.getPlayerTrains()[i].price)
                    {
                        currentArmor -= player.getPlayerTrains()[i].price;
                        upgradeTrains.push_back(player.getPlayerTrains()[i]);
                    } else
                        break;
                }
                if(player.getPlayerTrains()[0].price != 0)
                {
                    for(int i = 0; i < start; i++)
                    {
                        if(currentArmor > player.getPlayerTrains()[i].price)
                        {
                            currentArmor -= player.getPlayerTrains()[i].price;
                            upgradeTrains.push_back(player.getPlayerTrains()[i]);
                        } else
                            break;
                    }
                }
            }
            upgradeTrains.push_back(player.getPlayerTrains()[0]);
            socket->sendUpgradeMessage(true, upgradeTrains, player.getPlayerData().home_post_idx);
        } else if (player.getPlayerTrains()[player.getPlayerTrains().size() - 1].price <= currentArmor && player.getPlayerTrains()[player.getPlayerTrains().size() - 1].price != 0)
        {
            int start = 0;
            for(int i = 0; i < player.getPlayerTrains().size() - 1; i++)
            {
                if(player.getPlayerTrains()[i].level > player.getPlayerTrains()[i + 1].level)
                {
                    start = i + 1;
                    break;
                }
            }
            for(int i = start; i < player.getPlayerTrains().size(); i++)
            {
                if(currentArmor > player.getPlayerTrains()[i].price)
                {
                    currentArmor -= player.getPlayerTrains()[i].price;
                    upgradeTrains.push_back(player.getPlayerTrains()[i]);
                } else
                    break;
            }
            if(player.getPlayerTrains()[0].price != 0)
            {
                for(int i = 0; i < start; i++)
                {
                    if(currentArmor > player.getPlayerTrains()[i].price)
                    {
                        currentArmor -= player.getPlayerTrains()[i].price;
                        upgradeTrains.push_back(player.getPlayerTrains()[i]);
                    } else
                        break;
                }
            }
            socket->sendUpgradeMessage(false, upgradeTrains, player.getPlayerData().home_idx);
        }
        //socket->SendMessage(MAP,{{"layer", 1}});
        //map = *new Map1();
        //map.Pars(socket->getterDoc());
        qDebug() <<"FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEEEEEEEEEEEEEEEEEEEEEZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ";
        QVector <train> Trains;
        for(int i = 0; i < map.getTrains().size(); i++)
        {
            if(map.getTrains()[i].player_idx == player.getPlayerData().player_idx)
                Trains.append(map.getTrains()[i]);
        }
        player.setTrainsLevel(Trains);
        this->indexOfFirstArmorTrain = player.getPlayerTrains().size();
        int sum = 0;
        for(int i = 0; i < map.getterStorages().size(); i++)
            sum += map.getterStorages()[i].goods;
        int count = 0;
        while(sum > 0 && count < (player.getPlayerTrains().size() + 1) / 2 )
        {
            sum -= player.getPlayerTrains()[count].goods_capacity;
            count++;
            this->indexOfFirstArmorTrain--;
        }
        market Market = BestPost(map, GoodMarkets, player, map.getHome(player.getPlayerData().player_idx).point_idx);
        int lengthOfPathToMarket = shortestPaths[pointsOfGraph.indexOf(Market.point_idx)][0];
        sum = 0;
        for(int i = 0; i < indexOfFirstArmorTrain; i++)
            sum += player.getPlayerTrains()[count].goods_capacity;
        while((map.getHome(player.getPlayerData().player_idx).population * 2 * lengthOfPathToMarket + (lengthOfPathToMarket / 25) * lengthOfPathToMarket) * 1.5 > sum)
        {
            indexOfFirstArmorTrain++;
            sum += player.getPlayerTrains()[indexOfFirstArmorTrain - 1].goods_capacity;
            if(indexOfFirstArmorTrain == player.getPlayerTrains().size())
                break;
        }
        if(GoodMarkets.empty())
            GoodMarkets = markets;
        for(int i = 0; i < player.getPlayerTrains().size(); i++)
        {
            if(player.getPlayerTrains()[i].route.isEmpty())
            {
                MakeRoute(map, player, i < indexOfFirstArmorTrain, player.getPlayerTrains()[i]);
                pointsToVisit = player.getPlayerTrains()[i].postsRoute;
                if(!pointsToVisit.isEmpty())
                {
                    pointsToVisit.pop_back();
                }
                if(!player.getPlayerTrains()[i].postsRoute.isEmpty())
                {
                    QVector <int> route = alg.manipPaths(player.getPlayerData().home_idx,player.getPlayerTrains()[i].postsRoute.last(),pointsToVisit,pointsToAvoid);
                    player.setRoute(player.getPlayerTrains()[i].idx, route);
                    NotCrashFunction(player,player.getPlayerTrains()[i]);
                }
            }
        }

    }
}

market Strategy::BestPost(Map1 map, QVector <market> posts, Player player, int pos)
{
    QVector <market> rating(1);
    QVector <market> black_rating(1);
    for (int i = 0; i < posts.size(); i++)
    {
        qDebug() << this->shortestPaths[pointsOfGraph.indexOf(posts[i].point_idx)][0] -
                this->shortestPaths[pointsOfGraph.indexOf(pos)][0] + 1;
        if(player.getPlayerData().home_idx != pos)
            posts[i].mark = posts[i].goods / (this->shortestPaths[pointsOfGraph.indexOf(posts[i].point_idx)][0] -
                this->shortestPaths[pointsOfGraph.indexOf(pos)][0] + 1); //!!!!!
        else
            posts[i].mark = posts[i].goods / (this->shortestPaths[pointsOfGraph.indexOf(posts[i].point_idx)][0]);
        for(int j = 0; j < rating.size(); j++)
        {
            if (posts[i].mark == 0)
            {
                rating.insert(rating.size() - 1, posts[i]);
                break;
            }
            if (map.getHome(player.getPlayerData().player_idx).products < this->shortestPaths[pointsOfGraph.indexOf(posts[i].point_idx)][0]
                    * (map.getHome(player.getPlayerData().player_idx).population + ((2 * shortestPaths[pointsOfGraph.indexOf(posts[i].point_idx)][0]) / 25)))
            {
                black_rating.insert(j,posts[i]);
                break;
            }
            if(rating[j].mark < posts[i].mark)
            {
                rating.insert(j,posts[i]);
                break;
            }
            if(rating[j].mark == posts[i].mark)
            {
                if(this->shortestPaths[pointsOfGraph.indexOf(posts[i].point_idx)][0] < this->shortestPaths[pointsOfGraph.indexOf(rating[j].point_idx)][0]) {
                    rating.insert(j,posts[i]);
                }
                else {
                    if((j+1) == rating.size()) {
                        rating.push_back(posts[i]);
                    } else {
                        rating.insert(j + 1,posts[i]);
                    }
                }
                break;
            }
        }
    }
    rating.pop_back();
    black_rating.pop_back();
    if(rating.isEmpty())
        return black_rating[0];
    else
       return rating[0];
}

QVector <market> Strategy::GoodPosts(Map1 map, QVector <market> posts, Player player)
{
    QVector <market> rating;
    for(int i = 0; i < posts.size(); i++)
    {
        posts[i].mark = map.getHome(player.getPlayerData().player_idx).population * shortestPaths[pointsOfGraph.indexOf(posts[i].point_idx)][0] * 2;
        if(posts[i].mark < posts[i].goods)
        {
            rating.append(posts[i]);
        }
    }
    return rating;
}

void Strategy::MakeRoute(Map1 map, Player &player, bool isMarket, train Train)
{
    QVector <market> posts;
    QVector <int> route;
    int startTrain = 0, lastTrain = player.getPlayerTrains().size();
    if(isMarket)
    {
        posts = map.getterMarkets();
        lastTrain = indexOfFirstArmorTrain;
    }
    else
    {
        posts = map.getterStorages();
        startTrain = indexOfFirstArmorTrain;
    }
    for(int i = startTrain; i < lastTrain; i++)//и это вместо того чтобы перегрузить оператор ==, оторвите мне руки
    {
        for(int j = 0; j < player.getPlayerTrains()[i].postsRoute.size(); j++)
        {
            for(int k = 0; k < posts.size(); k++)
            {
                if(posts[k].point_idx == player.getPlayerTrains()[i].postsRoute[j])
                {
                    posts.erase(posts.begin() + k);//???
                    break;
                }
            }
        }
    }
    if(isMarket)
    {
        int goods_capacity = Train.goods_capacity;
        QVector <market> markets = map.getterMarkets();
        market Market;
        int numOfMarketPerTrain = markets.size() / indexOfFirstArmorTrain;
        int needProducts = 0;
        if(player.getPlayerTrains()[0].idx == Train.idx)
        {
            QVector <int> path;
            while((needProducts < map.getHome(player.getPlayerData().player_idx).products || player.getPlayerTrains()[0].postsRoute.size() < numOfMarketPerTrain + 1)
                  &&(goods_capacity > 0))
            {
                if(!path.isEmpty())
                    Market = BestPost(map, posts, player,path.last());
                else
                    Market = BestPost(map, posts, player,map.getHome(player.getPlayerData().player_idx).point_idx);
                QVector <int> temp;
                path.append(Market.point_idx);
                int lengthOfPathToMarket = CalculateLengthOfRoute(path);
                goods_capacity -= Market.goods;
                int del = 0;
                for(int i = 0; i < posts.size(); i++)
                {
                    if(posts[i].point_idx == Market.point_idx)
                    {
                        del = i;
                        break;
                    }
                }
                posts.erase(posts.begin() + del);
                //lengthOfPathToMarket = CalculateLengthOfRoute(path);
                needProducts = (map.getHome(player.getPlayerData().player_idx).population + (2 * lengthOfPathToMarket / 25)) * lengthOfPathToMarket * 2;
            }
            player.setPostsRoute(Train.idx,path);
        }
        else
            CreatePlanFunction(map, player, Train, posts);
    }
    else
    {
        CreatePlanFunction(map, player, Train, posts);
    }
}

void Strategy::NotCrashFunction(Player &player, train Train)
{
    int idx = 0;
    int current_length = CalculateLengthOfRoute(Train.route);
    for(int i = 0; i < player.getPlayerTrains().size(); i++)
    {
        if(Train.idx == player.getPlayerTrains()[i].idx)
        {
            idx = i;
            break;
        }
    }

    QVector <int> postsToVisit = Train.postsRoute;
    postsToVisit.pop_back();
    QVector <int> postsToAvoid;
    QVector <int> currentPath = Train.route;

    for(int i = 0; i < player.getPlayerTrains().size(); i++) //мммм алгоритмическая сложность куб, как мило
    {
        if(i != idx && !player.getPlayerTrains()[idx].route.isEmpty())
        {
            bool wrong = true;
             while(wrong)
            {
                if(player.getPlayerTrains()[i].route.isEmpty() || player.getPlayerTrains()[idx].route.size() < postsToVisit.size())
                    wrong = false;
                else {
                    for(int j = 1; j < player.getPlayerTrains()[idx].route.size(); j++)
                    {
                        if(player.getPlayerTrains()[i].route.indexOf(player.getPlayerTrains()[idx].route[j]) != -1 && i != idx)
                        {
                            postsToAvoid.append(pointsOfGraph[player.getPlayerTrains()[idx].route[j]]);
                            player.setRoute(Train.idx, alg.manipPaths(pointsOfGraph[player.getPlayerTrains()[idx].route[0]],
                                    pointsOfGraph[player.getPlayerTrains()[idx].route.last()], postsToVisit,postsToAvoid));
                            if(CalculateLengthOfRoute(player.getPlayerTrains()[idx].route) > (current_length + player.getPlayerTrains()[idx].waitIteration + 1) ||
                                    CalculateLengthOfRoute(player.getPlayerTrains()[idx].route) < current_length)
                            {
                                wrong = false;
                                if(player.getPlayerTrains()[i].position == Train.position && player.getPlayerTrains()[i].line_idx == Train.line_idx) //переделать!!
                                {
                                    player.setWaitIteration(Train.idx, player.getPlayerTrains()[idx].waitIteration + 1);
                                    player.setRoute(Train.idx, QVector <int> (0));
                                } else{
                                    postsToAvoid.pop_back();
                                    player.setRoute(Train.idx, currentPath);
                                }
                                break;
                            }
                            currentPath = player.getPlayerTrains()[i].route;
                            if(j == (player.getPlayerTrains()[idx].route.size() - 1) || j == (player.getPlayerTrains()[i].route.size() - 1))
                                wrong = false;
                            break;
                        }
                        if(j == (player.getPlayerTrains()[idx].route.size() - 1) || j == (player.getPlayerTrains()[i].route.size() - 1))
                        {
                            wrong = false;
                            break;
                        }
                    }
                }
            }
            if(!player.getPlayerTrains()[idx].route.isEmpty())
                player.setWaitIteration(Train.idx, 0);
        }
    }
}

void Strategy::CreatePlanFunction(Map1 map, Player &player, train Train, QVector <market> posts)
{
    int goods_capacity = Train.goods_capacity;
    QVector <int> path(0);
    while(goods_capacity > 0 && posts.size() != 0)
    {
        market Storage;
        if(!path.isEmpty())
            Storage = BestPost(map, posts, player,path.last());
        else
            Storage = BestPost(map, posts, player,map.getHome(player.getPlayerData().player_idx).point_idx);
        path.append(Storage.point_idx);
        goods_capacity -= Storage.goods;
        int del = 0;
        for(int i = 0; i < posts.size(); i++)
        {
            if(posts[i].point_idx == Storage.point_idx)
            {
                del = i;
                break;
            }
        }
        posts.erase(posts.begin() + del);
    }
    player.setPostsRoute(Train.idx,path);
}

int Strategy::CalculateLengthOfRoute(QVector <int> route)
{
    int length = 0;
    for(int i = 0; i < route.size() - 1; i++)
    {
        length += abs(this->shortestPaths[route[i]][0] - this->shortestPaths[route[i + 1]][0]);
    }
    return length;
}
