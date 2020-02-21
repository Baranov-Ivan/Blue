#ifndef MAINWINDOWFORCREATEMULTIGAME_H
#define MAINWINDOWFORCREATEMULTIGAME_H

#include <QMainWindow>
#include "mainwindow.h"
#include "askselect.h"
#include "Presenter/createmultiplayerpresenter.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindowForCreateMultigame;
}
QT_END_NAMESPACE

class MainWindowForCreateMultigame : public MainWindow
{
    Q_OBJECT

public:
    explicit MainWindowForCreateMultigame(QWidget *parent = nullptr);
    ~MainWindowForCreateMultigame() override;
    QJsonObject getLoginData() override;
    game * getGame() override;
    QString getGameName();
    int getNumOfPlayer();
    int getnumOfTurns();

private slots:
    void on_loginButton_clicked();
    void on_back_clicked();

private:
    Ui::MainWindowForCreateMultigame *ui;
    game Game;

};

#endif // MAINWINDOWFORCREATEMULTIGAME_H
