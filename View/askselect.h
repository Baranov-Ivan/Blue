#ifndef ASKSELECT_H
#define ASKSELECT_H

#include <QDialog>
#include "Presenter/mainwindowchangingpresenter.h"

namespace Ui {
class AskSelect;
}

class AskSelect : public QDialog
{
    Q_OBJECT

public:
    explicit AskSelect(QWidget *parent = nullptr);
    ~AskSelect();

private slots:
    void on_single_clicked();

    void on_createMultiplayer_clicked();

    void on_enterMultiplayer_clicked();

private:
    Ui::AskSelect *ui;
signals:
    void SinglePlayerChoosen();
    void EnterToExistingMultiplayerChoosen();
    void CreateMultiplayerChoosen();
};

#endif // ASKSELECT_H
