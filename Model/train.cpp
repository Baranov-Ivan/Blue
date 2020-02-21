#include "train.h"
#include "edge.h"
#include <QObject>

Train::Train(GraphWidget *graphWidget,QPointF begPos,QGraphicsPixmapItem *image)
    : graph(graphWidget)
{
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
    setImage(image);
    if(image != nullptr) {
        image->setZValue(2);
    }
    this->image->setPos(begPos.x() - (this->image->boundingRect().width())/2,begPos.y() - this->image->boundingRect().height());
}

void Train::setImage(QGraphicsPixmapItem* image)
{
    this->image= image;
}

void Train::advancePosition(Edge *edge,double coef,int curSpeed,int curPos,QTimeLine* animTimer) {
    QPointF sourcePoint = edge->getSourcePoint();
    QPointF destPoint = edge->getDestPoint();
    QRectF edgeRect = edge->boundingRect();
    double width = edgeRect.width();
    double height = edgeRect.height();
    double stepW = width/coef;
    double stepH = height/coef;

    double posForDraw = curPos;
    if(edge->getIdx() < 0 && curSpeed < 0) {
        sourcePoint = edge->getDestPoint();
        destPoint = edge->getSourcePoint();
    } else if (edge->getIdx() < 0 && curSpeed > 0) {
        posForDraw = coef - curPos;
    }

    if (sourcePoint.x() > destPoint.x()){
            stepW = -stepW;
    }

    if (sourcePoint.y() > destPoint.y()){
            stepH = -stepH;
    }

    double offsetW = (this->image->boundingRect().width())/2;
    double offsetH = this->image->boundingRect().height();

    //QTimeLine *timer = new QTimeLine(500);
    QGraphicsItemAnimation *animation = new QGraphicsItemAnimation();

    animation->setItem(this->image);
    //animation->setTimeLine(timer);
    animation->setTimeLine(animTimer);
    animation->setPosAt(1.0,QPointF(sourcePoint.x() + stepW*posForDraw - offsetW,sourcePoint.y() + stepH*posForDraw - offsetH));
    //timer->start();
}

QGraphicsPixmapItem* Train::getImage() {
    return this->image;
}

