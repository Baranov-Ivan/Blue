#include "mainwindowchangingpresenter.h"

MainWindowChangingPresenter::MainWindowChangingPresenter(QDialog *dialog)
{
    connect(&*(dialog),SIGNAL(SinglePlayerChoosen()), this, SLOT(OpenSinglePlayerGameWindow()));
    connect(&*(dialog), SIGNAL(EnterToExistingMultiplayerChoosen()), this, SLOT(OpenEnterToMultiplayerGameWindow()));
    connect(&*(dialog), SIGNAL(CreateMultiplayerChoosen()), this, SLOT(OpenCreatingMultiplayerGameWindow()));

}

MainWindowChangingPresenter::~MainWindowChangingPresenter()
{

}

void MainWindowChangingPresenter::OpenSinglePlayerGameWindow()
{
    MainWindow *window = new MainWindowForSinglePlay();
    delete this;
}

void MainWindowChangingPresenter::OpenEnterToMultiplayerGameWindow()
{
    MainWindow *window = new MainWindowForEnterExistingGame();
}

void MainWindowChangingPresenter::OpenCreatingMultiplayerGameWindow()
{
    MainWindow *window = new MainWindowForCreateMultigame();
}
