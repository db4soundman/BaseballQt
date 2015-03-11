#include "SeasonXMLHandler.h"
#include <QString>

SeasonXMLHandler::SeasonXMLHandler(BaseballTeam* t) {
    team = t;
    inPlayer = inTotals = inOpponent = foundGoalie =  false;
}

bool SeasonXMLHandler::startElement(const QString& namespaceURI,
                                    const QString& localName,
                                    const QString& qName,
                                    const QXmlAttributes& atts) {
    if (qName == "totals") {
        inTotals = true;
    }
    else if (qName == "opponent") {
        inOpponent = true;
    }

    else if (qName == "powerplay" && inTotals) {

    }

    else if (qName == "player") {
        currPlayer = new BaseballPlayer();
        inPlayer = true;
        currPlayer->setName(correctName(atts.value("name")));
        currPlayer->setUni(atts.value("uni"));
        currPlayer->setYear(atts.value("year"));
        currPlayer->setGp(atts.value("gp").toInt());
    }

    else if (qName == "shots" && inPlayer) {

    }

    else if (qName == "penalty" && inPlayer) {

    }

    else if (qName == "misc" && inPlayer) {

    }

    else if (qName == "goalie" && inPlayer) {


    }

    return true;
}

bool SeasonXMLHandler::endElement(const QString& namespaceURI, const QString& localName, const QString& qName) {
    if (qName == "player") {

        team->addPlayer(currPlayer);
        inPlayer = false;
        foundGoalie = false;
    }

    else if (qName == "totals") {
        inTotals = false;
    }

    else if (qName == "opponent") {
        inOpponent = false;
    }

    return true;
}

bool SeasonXMLHandler::characters(const QString& str)
{
    return true;
}

bool SeasonXMLHandler::fatalError(const QXmlParseException& exception)
{
    return false;
}

QString
SeasonXMLHandler::correctName(QString name) {
    if (!name.contains(",")) {
        return name.toUpper();
    }
    QString goodName = (name.mid(name.indexOf(",")) + " " +
                        name.left(name.indexOf(",")));
    return goodName.toUpper().trimmed();
}
