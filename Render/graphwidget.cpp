/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "graphwidget.h"
#include "Model/edge.h"
#include "Model/node.h"
#include "Model/train.h"
#include "Model/gamelogic.h"

#include <math.h>

#include <QKeyEvent>
#include <QVector>
#include <QRandomGenerator>
#include <QDebug>
#include <QHBoxLayout>
#include <QThread>

//! [0]
GraphWidget::GraphWidget(QWidget *parent, MainWindow *window, Player &player, Map0 layer0, Map1 layer1, Map10 layer10):QGraphicsView(parent),timerId_1(1)
{
    this->scene = new QGraphicsScene(this);
    this->edgeVec = edgeVec;

    this->layer0 = layer0;
    this->layer1 = layer1;
    this->layer10 = layer10;
    this->player = player;
    this->parent = window;
}
//! [1]

void GraphWidget::Render()
{
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    setScene(scene);

    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    scale(qreal(0.6), qreal(0.6));
    setMinimumSize(800, 600);
    setWindowTitle(tr("Train Simulator 2020"));


    QPixmap storage;
    QPixmap town;
    QPixmap market;
    QPixmap train;
    QPixmap enemyTrain;
    QPixmap enemyTown;
    QPixmap ghostTown;

    storage.load(":/resources/Pictures/storage_1.png");
    town.load(":/resources/Pictures/town.png");
    market.load(":/resources/Pictures/market.png");
    train.load(":/resources/Pictures/train.png");
    enemyTrain.load(":/resources/Pictures/train_enemy.png");
    enemyTown.load(":/resources/Pictures/town_enemy.png");
    ghostTown.load(":/resources/Pictures/town_ghost.png");
    scene->setSceneRect(0, 0, layer10.getSizeX(), layer10.getSizeY());
    Node* homeTown;

    QVector<int> pointsOfGraph = layer0.getterPointsOfgraph();

    QVector <post> posts = layer1.getterPosts();

    for(int i = 0; i < pointsOfGraph.size(); i++) {
        int a = -2;
        for(int j = 0; j < posts.size(); j++) {
            if(posts[j].point_idx == pointsOfGraph[i]) {
                a = posts[j].type;
                break;
            } else {
                a = -1;
            }
        }

        if(a == 1) {
            if(pointsOfGraph[i] == player.getPlayerData().home_idx) {
                nodeVec.append(new Node(this,pointsOfGraph[i],a,scene->addPixmap(town.scaled(QSize(76,76),Qt::IgnoreAspectRatio,Qt::SmoothTransformation))));
                homeTown = nodeVec.last();
            } else
            {
                for(int j = 0; j < layer1.getTown().size(); j++)
                {
                    if(pointsOfGraph[i] == layer1.getTown()[j].point_idx)
                    {
                        if(layer1.getTown()[j].player_idx != "" && layer1.getTown()[j].player_idx != player.getPlayerData().player_idx)
                            nodeVec.append(new Node(this,pointsOfGraph[i],a,scene->addPixmap(enemyTown.scaled(QSize(76,76),Qt::IgnoreAspectRatio,Qt::SmoothTransformation))));
                        else
                            nodeVec.append(new Node(this,pointsOfGraph[i],a,scene->addPixmap(ghostTown.scaled(QSize(76,76),Qt::IgnoreAspectRatio,Qt::SmoothTransformation))));
                        break;
                    }
                }
            }
        } else if(a == 2) {
            nodeVec.append(new Node(this,pointsOfGraph[i],a,scene->addPixmap(market.scaled(QSize(25,25),Qt::IgnoreAspectRatio,Qt::SmoothTransformation))));
        } else if(a == 3) {
            nodeVec.append(new Node(this,pointsOfGraph[i],a,scene->addPixmap(storage.scaled(QSize(25,25),Qt::IgnoreAspectRatio,Qt::SmoothTransformation))));
        } else {
            nodeVec.append(new Node(this,pointsOfGraph[i],a,nullptr));
        }

        scene->addItem(nodeVec.last());
        point curPoint = layer10.getCoordsByIdx(nodeVec.last()->getNodeIndex());
        nodeVec.last()->setPos(curPoint.x,curPoint.y);
        nodeVec.last()->setImagePosition(curPoint.x,curPoint.y);
    }

    QVector <QVector <int> > Table = layer0.getterTable();
    QVector <QVector <int> > Table_sym = Table;


    for(int i = 0; i < Table.size()-1; i++) {
        for(int j = i+1; j<Table[i].size();j++) {
            if(Table[i][j] != 0) {
                edgeVec.push_back(new Edge(nodeVec[i],nodeVec[j],Table[i][j],Table[j][i]));
                scene->addItem(edgeVec.last());
            }
            Table_sym[i][j] = abs(Table[i][j]);
            Table_sym[j][i] = abs(Table[i][j]);
        }
    }
    //shuffle();
    setParentWindow(parent);

    /*QList<Node *> nodes;
    foreach (QGraphicsItem *item, scene->items()) {
        if (Node *node = qgraphicsitem_cast<Node *>(item))
            nodes << node;
    }
    bool itemsMoved;
    do {
        foreach (Node *node, nodes)
            node->calculateForces();

        itemsMoved = false;
        foreach (Node *node, nodes) {
            if (node->advancePosition())
                itemsMoved = true;
        }
    } while(itemsMoved);*/

    if(pointsOfGraph.size() > 50) {
        scaleView(1/qreal(1.2*4.5));
    }


    getParentWindow()->setCentralWidget(this);

    this->edgeVec = edgeVec;

    this->layer0 = layer0;
    this->layer1 = layer1;
    this->player = player;

    this->playerTrain = playerTrain;

    for(int i = 0; i<this->player.getPlayerTrains().size(); i++) {
        this->player.setTrainImage(new Train(this,homeTown->pos(),scene->addPixmap(train.scaled(QSize(34,51),Qt::IgnoreAspectRatio,Qt::SmoothTransformation))),i);
    }
    emit RenderFinished(edgeVec, player);
}
//! [2]
void GraphWidget::itemMoved()
{
    //if (!timerId)
    //   timerId = startTimer(0);
}
//! [2]

//! [3]
void GraphWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Up:
        centerNode->moveBy(0, -20);
        break;
    case Qt::Key_Down:
        centerNode->moveBy(0, 20);
        break;
    case Qt::Key_Left:
        centerNode->moveBy(-20, 0);
        break;
    case Qt::Key_Right:
        centerNode->moveBy(20, 0);
        break;
    case Qt::Key_Plus:
        zoomIn();
        break;
    case Qt::Key_Minus:
        zoomOut();
        break;
    case Qt::Key_Space:
    case Qt::Key_Enter:
        shuffle();
        break;
    default:
        QGraphicsView::keyPressEvent(event);
    }
}
//! [3]

//! [4]
void GraphWidget::timerEvent(QTimerEvent *event) //создади таймер эвэнт
{
    Q_UNUSED(event)
    if(event->timerId() == timerId) {
        QList<Node *> nodes;
        foreach (QGraphicsItem *item, scene->items()) {
            if (Node *node = qgraphicsitem_cast<Node *>(item))
                nodes << node;
         }

        foreach (Node *node, nodes)
            node->calculateForces();

        bool itemsMoved = false;
        foreach (Node *node, nodes) {
            if (node->advancePosition())
                itemsMoved = true;
        }

        if (!itemsMoved) {
            killTimer(timerId);
            timerId = 0;
        }
    }

}
//! [4]

#if QT_CONFIG(wheelevent)
//! [5]
void GraphWidget::wheelEvent(QWheelEvent *event)
{
    scaleView(pow((double)2, -event->delta() / 240.0));
}
//! [5]
#endif

//! [6]
void GraphWidget::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect)

    // Shadow
    QRectF sceneRect = this->sceneRect();
    QRectF rightShadow(sceneRect.right(), sceneRect.top() + 5, 5, sceneRect.height());
    QRectF bottomShadow(sceneRect.left() + 5, sceneRect.bottom(), sceneRect.width(), 5);
    if (rightShadow.intersects(rect) || rightShadow.contains(rect))
        painter->fillRect(rightShadow, Qt::darkGray);
    if (bottomShadow.intersects(rect) || bottomShadow.contains(rect))
        painter->fillRect(bottomShadow, Qt::darkGray);

    // Fill
    QLinearGradient gradient(sceneRect.topLeft(), sceneRect.bottomRight());
    gradient.setColorAt(0, Qt::white);
    gradient.setColorAt(1, Qt::lightGray);
    painter->fillRect(rect.intersected(sceneRect), gradient);
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(sceneRect);

    // Text
    // Осталось от исходника. Не удалял. Пригодится как пример для отрисовки текста
    /*QRectF textRect(sceneRect.left() + 4, sceneRect.top() + 4,
                    sceneRect.width() - 4, sceneRect.height() - 4);
    QString message(tr("Click and drag the nodes around, and zoom with the mouse "
                       "wheel or the '+' and '-' keys"));

    QFont font = painter->font();
    font.setBold(true);
    font.setPointSize(14);
    painter->setFont(font);
    painter->setPen(Qt::lightGray);
    painter->drawText(textRect.translated(2, 2), message);
    painter->setPen(Qt::black);
    painter->drawText(textRect, message);*/
}
//! [6]

//! [7]
void GraphWidget::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}
//! [7]

void GraphWidget::shuffle()
{
    foreach (QGraphicsItem *item, scene->items()) {
        if (qgraphicsitem_cast<Node *>(item))
            item->setPos(-150 + QRandomGenerator::global()->bounded(300), -150 + QRandomGenerator::global()->bounded(300));
    }
}

void GraphWidget::zoomIn()
{
    scaleView(qreal(1.2));
}

void GraphWidget::zoomOut()
{
    scaleView(1 / qreal(1.2));
}

void GraphWidget::setParentWindow(MainWindow *window)
{
    this->parent = window;
}

MainWindow* GraphWidget::getParentWindow() const
{
    return parent;
}

void GraphWidget::Update(town Town)
{
    QPixmap enemyTown;
    enemyTown.load(":/resources/Pictures/town_enemy.png");
    for(int i = 0; i < nodeVec.size(); i++)
    {
        if(nodeVec[i]->getNodeIndex() == Town.point_idx)
        {
            nodeVec[i]->setImage(scene->addPixmap(enemyTown.scaled(QSize(76,76),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
            break;
        }
    }
}


QGraphicsScene* GraphWidget::getScene() {
    return this->scene;
}

void GraphWidget::SetEnemyTrains(enemy Enemy, Player& player)
{
    for(int j = 0; j < nodeVec.size(); j++)
    {
        if(nodeVec[j]->getNodeIndex() == Enemy.Town.point_idx)
        {
           qDebug()<<"Trying to set enemy trains!!!!!!!!!!!";
           QPixmap enemyTrain;
           enemyTrain.load(":/resources/Pictures/train_enemy.png");

           for(int z = 0; z < Enemy.trains.size(); z++)
           {
              player.setEnemyTrainImage(new Train(this,nodeVec[j]->pos(),scene->addPixmap(enemyTrain.scaled(QSize(34,51),Qt::IgnoreAspectRatio,Qt::SmoothTransformation))),
                                              Enemy.player_idx,Enemy.trains[z].idx);
           }
        }
    }

}
