#include "View/mainwindowforsingleplay.h"
#include "ui_mainwindowforsingleplay.h"

MainWindowForSinglePlay::MainWindowForSinglePlay(QMainWindow *parent) :
    MainWindow(parent),
    ui(new Ui::MainWindowForSinglePlay)
{
    ui->setupUi(this);
    SinglePlayerPresenter *presenter = new SinglePlayerPresenter(this, new SocketService());
    this->show();
}

MainWindowForSinglePlay::~MainWindowForSinglePlay()
{
    delete ui;
}

void MainWindowForSinglePlay::on_pushButton_clicked()
{
    loginText = ui->login->text();
    emit StartGame();
}

QString MainWindowForSinglePlay::getLoginText()
{
    return loginText;
}

void MainWindowForSinglePlay::on_back_clicked()
{
    emit BackPush();
    this->close();
}

QJsonObject MainWindowForSinglePlay::getLoginData()
{
    return {{"name", loginText}};
}

game* MainWindowForSinglePlay::getGame()
{
    Game.gameName = "Game of " + loginText;
    Game.gameState = INIT;
    Game.numberOfTurns = -1;
    Game.numberOfPlayers = 1;
    return &Game;
}
