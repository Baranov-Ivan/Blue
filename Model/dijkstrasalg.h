#ifndef DIJKSTRASALG_H
#define DIJKSTRASALG_H

#include <QVector>
#include <QDebug>
#include "structs.h"

class DijkstrasAlg
{
public:
    DijkstrasAlg(int townIdx,QVector <QVector <int> > &Table, QVector<int> &pointsOfGraph, QVector<post> posts);
    QVector <QVector <int> > getPaths();
    QVector <int> manipPaths(int startpIdx, int endpIdx, QVector<int> &postsToVisit, QVector<int> &postsToAvoid);
    QVector <QVector <int> > shortestPaths;
    QVector <int> Path(bool fromTown, int pointIdx);
private:
    QVector<QVector<int>> shPathsFunc2(int rawIdx, QVector<QVector<int> > &Table);
    QVector <int> Path2(int rawIdx, const QVector<QVector<int> > &shPaths);
    void removePosts(const QVector<int> &postsToRemove,QVector <QVector <int> > &tempTable);
    QVector<int> pointsOfGraph;
    QVector<QVector<int>> Table;
};

#endif // DIJKSTRASALG_H
