#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

}

MainWindow::~MainWindow()
{
   // delete ui;
}

SocketTest* MainWindow::getSocket()
{
    return this->Socket;
}
