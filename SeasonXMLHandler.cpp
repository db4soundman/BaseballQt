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
        currPlayer = BaseballPlayer();
        inPlayer = true;
        currPlayer.setName(correctName(atts.value("name")));
        currPlayer.setUni(atts.value("uni"));
        currPlayer.setYear(atts.value("year"));
        currPlayer.setGp(atts.value("gp").toInt());
        currPlayer.setBats(atts.value("bats"));
        currPlayer.setThrows(atts.value("throws"));
    }

    else if (qName == "hitting" && inPlayer) {
        currPlayer.setSacFly(atts.value("sf").toInt());
        currPlayer.setHbp(atts.value("hbp").toInt());
        currPlayer.setStrikeouts(atts.value("so").toInt());
        currPlayer.setWalks(atts.value("bb").toInt());
        currPlayer.setHr(atts.value("hr").toInt());
        currPlayer.setTriples(atts.value("triple").toInt());
        currPlayer.setDoubles(atts.value("double").toInt());
        currPlayer.setRbi(atts.value("rbi").toInt());
        currPlayer.setAb(atts.value("ab").toInt());
        currPlayer.setR(atts.value("r").toInt());
        currPlayer.setH(atts.value("h").toInt());
    }

    else if (qName == "pitching" && inPlayer) {
        currPlayer.setEra(atts.value("era"));
        currPlayer.setAp(atts.value("appear").toInt());
        currPlayer.setGs(atts.value("gs").toInt());
        currPlayer.setSaves(atts.value("save").toInt());
        currPlayer.setWins(atts.value("win").toInt());
        currPlayer.setLosses(atts.value("loss").toInt());
        currPlayer.setHitsAllowed(atts.value("h").toInt());
        currPlayer.setRunsAllowed(atts.value("r").toInt());
        currPlayer.setEr(atts.value("er").toInt());
        currPlayer.setBb(atts.value("bb").toInt());
        currPlayer.setKOut(atts.value("k").toInt());
        double ip = atts.value("ip").toDouble();
        currPlayer.setOuts(((int) (ip) * 3) + ((int) (ip*10)) % 10);
    }

    return true;
}

bool SeasonXMLHandler::endElement(const QString& namespaceURI, const QString& localName, const QString& qName) {
    if (qName == "player") {

        team->addPlayer(currPlayer);
        inPlayer = false;
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
    else if (name.contains(", ")){
        std::string goodName = name.toStdString();
        QString firstName = QString::fromStdString(goodName.substr(goodName.find(" ") + 1, goodName.length()));
        QString lastName = QString::fromStdString(goodName.substr(0, goodName.find(",")));
        name = firstName.toUpper() + " " + lastName.toUpper();
    }
    else if (name.contains(",")) {
        std::string goodName = name.toStdString();
        QString firstName = QString::fromStdString(goodName.substr(goodName.find(",") + 1, goodName.length()));
        QString lastName = QString::fromStdString(goodName.substr(0, goodName.find(",")));
        name = firstName.toUpper() + " " + lastName.toUpper();
    }
    return name;
}
