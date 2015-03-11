#include "GameXmlUpdater.h"

GameXmlUpdater::GameXmlUpdater(BaseballGame* game, BaseballTeam* awayTeam, BaseballTeam* homeTeam) {
    this->game = game;
    this->awayTeam = awayTeam;
    this->homeTeam = homeTeam;

    inAwayTeam = inTotals = inPlayer = false;
}

bool
GameXmlUpdater::startElement(const QString& namespaceURI,
                                  const QString& localName,
                                  const QString& qName,
                                  const QXmlAttributes& atts) {
    if (qName == "team") {
        if (atts.value("vh") == "V") {
            inAwayTeam = true;
        }
    }

    else if (qName == "totals") {
        inTotals = true;
    }

    else if (qName == "shots" && inTotals) {
        if (inAwayTeam) {

        }
        else {

        }
    }

    else if (qName == "player" && atts.value("uni") != "TM") {
        inPlayer = true;
        if (atts.value("gp") == "1") {
            curPlayer = inAwayTeam ? awayTeam->getPlayerByNumber(atts.value("uni")) :
                                     homeTeam->getPlayerByNumber(atts.value("uni"));
        }
        else {
            curPlayer = NULL;
        }
    }

    else if (curPlayer != NULL && inPlayer) {
        if (qName == "shots") {

        }
        else if (qName == "penalty") {

        }
        else if (qName == "goalie" ) {

        }
    }

    return true;
}

bool GameXmlUpdater::endElement(const QString& namespaceURI, const QString& localName, const QString& qName) {

    if (qName == "totals") {
        inTotals = false;
    }

    else if (qName == "team") {
        inAwayTeam = false;
        inPlayer = false;
        curPlayer = NULL;
    }

    else if (qName == "player") {
        inPlayer = false;
    }

    return true;
}

bool GameXmlUpdater::characters(const QString& str)
{

    return true;
}

bool GameXmlUpdater::fatalError(const QXmlParseException& exception)
{
    return false;
}


