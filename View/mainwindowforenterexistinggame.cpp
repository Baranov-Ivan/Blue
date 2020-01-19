#include "mainwindowforenterexistinggame.h"
#include "ui_mainwindowforenterexistinggame.h"

MainWindowForEnterExistingGame::MainWindowForEnterExistingGame(QWidget *parent) :
    MainWindow(parent),
    ui(new Ui::MainWindowForEnterExistingGame)
{
    EnterExistingGamePresenter *presenter = new EnterExistingGamePresenter(this, new SocketService);
    connect(&*(presenter),SIGNAL(ShowGames(ExistingGames )), &*(this), SLOT(ShowGames(ExistingGames )));
    ui->setupUi(this);
    presenter->AskExistingGames();
    this->show();
}

MainWindowForEnterExistingGame::~MainWindowForEnterExistingGame()
{
    delete ui;
}

void MainWindowForEnterExistingGame::on_refresh_clicked()
{
    ui->gameList->clear();
    emit Refresh();
}

void MainWindowForEnterExistingGame::on_login_clicked()
{
    emit StartGame();
}


QJsonObject MainWindowForEnterExistingGame::getLoginData()
{
    return {{"name", this->ui->login_2->text()},{"game", getGameName()}};
}

game* MainWindowForEnterExistingGame::getGame()
{
    Game.gameName = getGameName();
    Game.gameState = INIT;
    Game.numberOfTurns = -1;
    Game.numberOfPlayers = 2;//def
    return &Game;
}

QString MainWindowForEnterExistingGame::getGameName()
{
    return this->ui->gameList->currentText();
}


void MainWindowForEnterExistingGame::ShowGames(ExistingGames games)
{
    QStringList GameList;
    this->gameList = games.getGames();
    for(int i = 0; i < gameList.size(); i++)
    {
        GameList.append(this->gameList[i].gameName);
    }
    ui->gameList->addItems(GameList);
}

void MainWindowForEnterExistingGame::on_back_clicked()
{
    AskSelect *askSelect = new AskSelect();
    askSelect->show();
    this->close();
}
