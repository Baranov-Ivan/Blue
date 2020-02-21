#include "statslabel.h"

StatsLabel::StatsLabel(GraphWidget *parent, QString string) {
    QFont *font = new QFont("Helvetica", 20, QFont::Bold);
    setFont(*font);
    setText(string);
    show();
}

void StatsLabel::updateString(QString string) {
    this->setText(string);
}
