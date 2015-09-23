#include "GameXmlHandler.h"

GameXmlHandler::GameXmlHandler(BaseballTeam* t) {
    team = t;
}

bool GameXmlHandler::startElement(const QString& namespaceURI,
                                const QString& localName,
                                const QString& qName,
                                const QXmlAttributes& atts) {
    if (qName == "player") {
        currPlayer = new BaseballPlayer();

    }

    return true;
}

bool GameXmlHandler::endElement(const QString& namespaceURI, const QString& localName, const QString& qName) {
if (qName == "player") {
    team->addPlayer(currPlayer);
}

else if (qName == "team") {
    return false;
}

return true;
}

bool GameXmlHandler::characters(const QString& str)
{
return true;
}

bool GameXmlHandler::fatalError(const QXmlParseException& exception)
{
return false;
}

QString
GameXmlHandler::correctName(QString name) {
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
