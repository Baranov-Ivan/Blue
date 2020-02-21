
#include "dijkstrasalg.h"
#include <iostream>


DijkstrasAlg::DijkstrasAlg(int townIdx, QVector<QVector<int> > &Table, QVector<int> &pointsOfGraph, QVector<post> posts)
{
    this->Table = Table;
    this->pointsOfGraph = pointsOfGraph;
    this->shortestPaths = shPathsFunc2(townIdx, Table);
}

QVector<int> DijkstrasAlg::Path(bool fromTown, int pointIdx)
{
    QVector <int> path;
    path.append(pointsOfGraph.indexOf(pointIdx));
    for(int i = pointsOfGraph.indexOf(pointIdx);shortestPaths[i][1]!=0;i = shortestPaths[i][1])
    {
        path.append(shortestPaths[i][1]);
    }
    path.append(0);
    if(fromTown) std::reverse(path.begin(),path.end());
    return path;
}

QVector<int> DijkstrasAlg::Path2(int rawIdx, const QVector<QVector<int> > &shPaths)
{
    QVector <int> path;
    for(int i = rawIdx;shPaths[i][1]!=INT_MAX;i = shPaths[i][1])
    {
        path.append(shPaths[i][1]);
    }
    std::reverse(path.begin(),path.end());
    return path;
}

QVector <QVector <int> > DijkstrasAlg::getPaths() {
    return shortestPaths;
}

QVector<int> DijkstrasAlg::manipPaths(int startpIdx, int endpIdx, QVector<int> &postsToVisit, QVector<int> &postsToAvoid)
{
    QVector<int> points;
    QVector<int> resultPath;
    QVector<QVector<int>> tempTable = Table;
    removePosts(postsToAvoid, tempTable);
    points.append(startpIdx);
    points.append(postsToVisit);
    QVector <bool> visited(points.size(), false);
    int z = pointsOfGraph.indexOf(points[0]);
    visited[0] = true;
    for(int i = 0;i<points.size()-1;i++)
    {
        QVector<QVector<int>> shPaths = shPathsFunc2(z,tempTable); //shortest paths from the point z
        int min = INT_MAX;
        int jSave=0;
        for(int j = 0;j<points.size();j++)
        {
            if(visited[j]==true) continue;
            int tempIdx = pointsOfGraph.indexOf(points[j]);
            if(min>shPaths[tempIdx][0])
            {
                 min = shPaths[tempIdx][0];
                 z = tempIdx;
                 jSave = j;
            }
        }
        visited[jSave] = true;
        resultPath.append(Path2(z,shPaths));
    }
    QVector<QVector<int>> shPaths = shPathsFunc2(z,tempTable);
    z = pointsOfGraph.indexOf(endpIdx);
    resultPath.append(Path2(z,shPaths));
    resultPath.append(z);
    return resultPath;
}

QVector <QVector <int> > DijkstrasAlg::shPathsFunc2(int rawIdx, QVector<QVector<int> > &Table)
{
    int n = pointsOfGraph.size();
    QVector <QVector <int> > shortestPaths(n, QVector <int>(2, INT_MAX));
    QVector <bool> visited(n);
    for(int i=0;i<n;i++) {
        if(Table[rawIdx][i]>0)
        {
            shortestPaths[i][0]=Table[rawIdx][i];
            shortestPaths[i][1]=rawIdx;
        }
        visited[i]=false;
    }
    shortestPaths[rawIdx][0]=0;
    //shortestPaths[rawIdx][1]=0;
    int index1=0,u=0;
    for (int i=0;i<n;i++)
    {
        int min=INT_MAX;
        for (int j=0;j<n;j++)
        {
            if (!visited[j] && shortestPaths[j][0]<min)
            {
                min=shortestPaths[j][0];
                index1=j;
            }
        }
        u=index1;
        visited[u]=true;
        for(int j=0;j<n;j++)
        {
            if (!visited[j] && Table[u][j]!=0 && (shortestPaths[u][0]+Table[u][j]<shortestPaths[j][0]))
            {
                shortestPaths[j][0]=shortestPaths[u][0]+Table[u][j];
                shortestPaths[j][1]=u;
            }
        }
    }
    return shortestPaths;
}

//nulls edges to passed posts by way of avoiding them
void DijkstrasAlg::removePosts(const QVector<int> &postsToRemove, QVector<QVector<int> > &tempTable)
{
    int pSize = pointsOfGraph.size();
    int mSize = postsToRemove.size();
    for(int i = 0;i<mSize;i++)
    {
        int index = pointsOfGraph.indexOf(postsToRemove[i]);
        for(int k = 0;k<pSize;k++)
        {
            tempTable[index][k] = 0;
            tempTable[k][index] = 0;
        }
    }
}
