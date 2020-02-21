#ifndef MAINWINDOWFORSINGLEPLAY_H
#define MAINWINDOWFORSINGLEPLAY_H

//#include <QMainWindow>
#include "mainwindow.h"
#include "askselect.h"
#include "Model/socketservice.h"
#include "Presenter/singleplayerpresenter.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindowForSinglePlay;
}
QT_END_NAMESPACE

class MainWindowForSinglePlay : public MainWindow
{
    Q_OBJECT

public:
    explicit MainWindowForSinglePlay(QMainWindow *parent = nullptr);
    ~MainWindowForSinglePlay() override;
    QString getLoginText();
    QJsonObject getLoginData() override;
    game * getGame() override;

private slots:
    void on_pushButton_clicked();
    void on_back_clicked();

private:
    Ui::MainWindowForSinglePlay *ui;
    game Game;
    QString loginText;
};

#endif // MAINWINDOWFORSINGLEPLAY_H
