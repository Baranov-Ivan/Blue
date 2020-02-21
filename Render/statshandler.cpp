#include "statshandler.h"

StatsHandler::StatsHandler(GraphWidget *parent, QString playerName, QString townName) {
    QFont *font = new QFont("Helvetica", 20, QFont::Bold);

    this->playerName.setFont(*font);
    this->townName.setFont(*font);
    populationString.setFont(*font);
    productString.setFont(*font);
    armorString.setFont(*font);
    ratingString.setFont(*font);
    populationValue.setFont(*font);
    productValue.setFont(*font);
    armorValue.setFont(*font);
    ratingValue.setFont(*font);

    this->playerName.setText("Player: " + playerName);
    this->townName.setText("Hometown: " + townName);
    populationString.setText("Population:");
    productString.setText("Product:");
    armorString.setText("Armor:");
    ratingString.setText("Rating:");

    this->playerName.setParent(parent);
    this->townName.setParent(parent);
    populationString.setParent(parent);
    productString.setParent(parent);
    armorString.setParent(parent);
    ratingString.setParent(parent);
    populationValue.setParent(parent);
    productValue.setParent(parent);
    armorValue.setParent(parent);
    ratingValue.setParent(parent);

    //add setGeometry and show
}
