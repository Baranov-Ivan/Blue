#include "askselect.h"
#include "ui_askselect.h"

AskSelect::AskSelect(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AskSelect)
{
    MainWindowChangingPresenter *presenter = new MainWindowChangingPresenter(this);
    ui->setupUi(this);
    this->show();
}

AskSelect::~AskSelect()
{
//    delete ui;
}

void AskSelect::on_single_clicked()
{
    emit SinglePlayerChoosen();
    this->close();
}

void AskSelect::on_createMultiplayer_clicked()
{
    emit CreateMultiplayerChoosen();
    this->close();
}

void AskSelect::on_enterMultiplayer_clicked()
{
    emit EnterToExistingMultiplayerChoosen();
    this->close();
}
