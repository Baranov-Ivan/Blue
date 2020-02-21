#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "Model/sockettest.h"
//#include "graphwidget.h"
#include "Model/structs.h"
#include "Model/edge.h"
#include "Model/train.h"
#include "Model/node.h"
#include "Model/dijkstrasalg.h"
#include <QMainWindow>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    virtual game* getGame() = 0;
    SocketTest* getSocket();
    virtual QJsonObject getLoginData() = 0;
signals:
    void BackPush();
    void StartGame();

protected:
    SocketTest *Socket;
    game *Game;
    //Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
