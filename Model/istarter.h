#ifndef ISTARTER_H
#define ISTARTER_H

#include <QObject>
#include "socketservice.h"

class IStarter:public QObject
{
public:
    virtual ~IStarter(){}
    virtual void StartGameLogic() = 0;
public slots:
    virtual void CheckAndStart() = 0;
    virtual void Check() = 0;
};

#endif // ISTARTER_H
