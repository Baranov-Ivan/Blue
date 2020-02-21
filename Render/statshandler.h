#ifndef STATSHANDLER_H
#define STATSHANDLER_H
#include <QLabel>
#include "graphwidget.h"

class StatsHandler {
public:
    StatsHandler(GraphWidget *parent,QString playerName,QString townName);
    void setPopulationValue(int population);
    void setProductValue(int product);
    void setArmorValue(int armor);
    void setRatingValue(int rating);

private:
    QLabel playerName;
    QLabel townName;
    QLabel populationString;
    QLabel productString;
    QLabel armorString;
    QLabel ratingString;

    QLabel populationValue;
    QLabel productValue;
    QLabel armorValue;
    QLabel ratingValue;
};

#endif // STATSHANDLER_H
