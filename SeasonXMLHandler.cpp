#include "SeasonXMLHandler.h"
#include <QString>

SeasonXMLHandler::SeasonXMLHandler(BaseballTeam* t) {
    team = t;
    inPlayer = inTotals = inOpponent = foundPitcher =  false;
}

bool SeasonXMLHandler::startElement(const QString& namespaceURI,
                                    const QString& localName,
                                    const QString& qName,
                                    const QXmlAttributes& atts) {
    if (qName == "player") {
        currPlayer = new BaseballPlayer();
        inPlayer = true;
        currPlayer->setName(correctName(atts.value("name")));
        currPlayer->setUni(atts.value("uni"));
        currPlayer->setYear(atts.value("year"));
        currPlayer->setGp(atts.value("gp").toInt());
    }

    else if (qName == "hitting" && inPlayer) {
        currPlayer->setSacFly(atts.value("sf").toInt());
        currPlayer->setHbp(atts.value("hbp").toInt());
        currPlayer->setStrikeouts(atts.value("so").toInt());
        currPlayer->setWalks(atts.value("bb").toInt());
        currPlayer->setHr(atts.value("hr").toInt());
        currPlayer->setTriples(atts.value("triple").toInt());
        currPlayer->setDoubles(atts.value("double").toInt());
        currPlayer->setRbi(atts.value("rbi").toInt());
        currPlayer->setAb(atts.value("ab").toInt());
        currPlayer->setR(atts.value("r").toInt());
        currPlayer->setH(atts.value("h").toInt());
    }

    else if (qName == "pitching" && inPlayer) {
        currPlayer->setEra(atts.value("era"));
        currPlayer->setAp(atts.value("appear").toInt());
        currPlayer->setGs(atts.value("gs").toInt());
        currPlayer->setSaves(atts.value("save").toInt());
        currPlayer->setWins(atts.value("win").toInt());
        currPlayer->setLosses(atts.value("loss").toInt());
        currPlayer->setHitsAllowed(atts.value("h").toInt());
        currPlayer->setRunsAllowed(atts.value("r").toInt());
        currPlayer->setEr(atts.value("er").toInt());
        currPlayer->setBb(atts.value("bb").toInt());
        currPlayer->setKOut(atts.value("k").toInt());
        double ip = atts.value("ip").toDouble();
        currPlayer->setOuts(((int) (ip) * 3) + ((int) (ip*10)) % 10);
    }

    return true;
}

bool SeasonXMLHandler::endElement(const QString& namespaceURI, const QString& localName, const QString& qName) {
    if (qName == "player") {

        team->addPlayer(currPlayer);
        inPlayer = false;
    }

    else if (qName == "bbseas") {
        currPlayer = new BaseballPlayer();
        currPlayer->setName("NO NAME");
        currPlayer->setUni("");
        currPlayer->setYear("");
        currPlayer->setGp(0);
        currPlayer->setSacFly(0);
        currPlayer->setHbp(0);
        currPlayer->setStrikeouts(0);
        currPlayer->setWalks(0);
        currPlayer->setHr(0);
        currPlayer->setTriples(0);
        currPlayer->setDoubles(0);
        currPlayer->setRbi(0);
        currPlayer->setAb(0);
        currPlayer->setAp(0);
        currPlayer->setGs(0);
        currPlayer->setSaves(0);
        currPlayer->setWins(0);
        currPlayer->setLosses(0);
        currPlayer->setHitsAllowed(0);
        currPlayer->setRunsAllowed(0);
        currPlayer->setEr(0);
        currPlayer->setBb(0);
        currPlayer->setKOut(0);
        team->addPlayer(currPlayer);
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
        name = name.toUpper();
    }
    else {
        std::string goodName = name.toStdString();
        QString firstName = QString::fromStdString(goodName.substr(goodName.find(" ") + 1, goodName.length()));
        QString lastName = QString::fromStdString(goodName.substr(0, goodName.find(",")));
        name = firstName.toUpper() + " " + lastName.toUpper();
    }
    return name;
}
