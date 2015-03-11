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
    return name.toUpper();
}
QString goodName = (name.mid(name.indexOf(",")) + " " +
                    name.left(name.indexOf(",")));
return goodName.toUpper().trimmed();
}
