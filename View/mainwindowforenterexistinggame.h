#ifndef MAINWINDOWFORENTEREXISTINGGAME_H
#define MAINWINDOWFORENTEREXISTINGGAME_H

#include <QMainWindow>
#include "mainwindow.h"
#include "Model/structs.h"
#include "askselect.h"
#include "Presenter/enterexistinggamepresenter.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindowForEnterExistingGame;
}
QT_END_NAMESPACE

class MainWindowForEnterExistingGame : public MainWindow
{
    Q_OBJECT

public:
    explicit MainWindowForEnterExistingGame(QWidget *parent = nullptr);
    ~MainWindowForEnterExistingGame() override;
    QJsonObject getLoginData() override;
    game * getGame() override;
    QString getGameName();

private slots:
    void on_refresh_clicked();

    void on_login_clicked();
    void on_back_clicked();

public slots:
    void ShowGames(ExistingGames games);

private:
    Ui::MainWindowForEnterExistingGame *ui;
    QVector <game> gameList;
    game Game;
signals:
    void Refresh();
};

#endif // MAINWINDOWFORENTEREXISTINGGAME_H
