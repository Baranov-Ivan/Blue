#include "mainwindowforcreatemultigame.h"
#include "ui_mainwindowforcreatemultigame.h"

MainWindowForCreateMultigame::MainWindowForCreateMultigame(QWidget *parent) :
    MainWindow(parent),
    ui(new Ui::MainWindowForCreateMultigame)
{
    CreateMultiplayerPresenter *presenter = new CreateMultiplayerPresenter(this, new SocketService);
    ui->setupUi(this);
    this->show();
}

MainWindowForCreateMultigame::~MainWindowForCreateMultigame()
{
    delete ui;
}

void MainWindowForCreateMultigame::on_loginButton_clicked()
{
    emit StartGame();
}


void MainWindowForCreateMultigame::on_back_clicked()
{
    AskSelect *askSelect = new AskSelect();
    askSelect->show();
    this->close();
}

QJsonObject MainWindowForCreateMultigame::getLoginData()
{
    return {{"name", this->ui->login->text()},{"game", getGameName()},{"nam_turns", getnumOfTurns()}, {"num_players", getNumOfPlayer()}};
}

game* MainWindowForCreateMultigame::getGame()
{
    Game.gameName = getGameName();
    Game.gameState = INIT;
    Game.numberOfTurns = getnumOfTurns();
    Game.numberOfPlayers = getNumOfPlayer();
    return &Game;
}

QString MainWindowForCreateMultigame::getGameName()
{
    return this->ui->gameName->text();
}

int MainWindowForCreateMultigame::getnumOfTurns()
{
    return this->ui->numberOfTurns->text().toInt();
}

int MainWindowForCreateMultigame::getNumOfPlayer()
{
    return this->ui->numberOfPlayers->text().toInt();
}
