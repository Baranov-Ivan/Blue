#ifndef STATSLABEL_H
#define STATSLABEL_H

#include <QLabel>
#include "graphwidget.h"

class StatsLabel : public QLabel {
public:
   StatsLabel(GraphWidget *parent,QString string);
   void updateString(QString string);
};
#endif // STATSLABEL_H
