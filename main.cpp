#include "View/askselect.h"
#include <QApplication>
#include <QCoreApplication>
#include "QDialog"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AskSelect askSelect;
    return a.exec();
}
