#ifndef TRAIN_H
#define TRAIN_H

#include <QGraphicsPixmapItem>
#include <QTimeLine>
#include <QGraphicsItemAnimation>
//#include "graphwidget.h"

class Edge;
class GraphWidget;
class Node;

class Train : public QGraphicsPixmapItem
{
public:
    Train(GraphWidget *graphWidget,QPointF begPos,QGraphicsPixmapItem *image);

    enum { Type = UserType + 1 };
    int type() const override { return Type; }

    void setImage(QGraphicsPixmapItem *image);
    void advancePosition(Edge *edge,double coef,int curSpeed,int curPos,QTimeLine* animTimer);
    QGraphicsPixmapItem* getImage();

private:
    Edge* currEdge;
    QGraphicsPixmapItem* image;
    GraphWidget* graph;
};
//! [0]

#endif // TRAIN_H
