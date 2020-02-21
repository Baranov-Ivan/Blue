#ifndef MAINWINDOWCHANGINGPRESENTER_H
#define MAINWINDOWCHANGINGPRESENTER_H

#include "View/mainwindow.h"
#include "View/askselect.h"
#include "View/mainwindowforcreatemultigame.h"
#include "View/mainwindowforenterexistinggame.h"
#include "View/mainwindowforsingleplay.h"

class MainWindowChangingPresenter:public QObject
{
    Q_OBJECT
public:
    explicit MainWindowChangingPresenter(QDialog *parent);
    virtual ~MainWindowChangingPresenter();
public slots:
    void OpenSinglePlayerGameWindow();
    void OpenEnterToMultiplayerGameWindow();
    void OpenCreatingMultiplayerGameWindow();
};

#endif // MAINWINDOWCHANGINGPRESENTER_H
