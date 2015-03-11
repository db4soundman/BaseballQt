#ifndef GAMEXMLUPDATER_H
#define GAMEXMLUPDATER_H

#include <QXmlDefaultHandler>
#include <QFile>
#include "BaseballGame.h"
#include "BaseballTeam.h"

class GameXmlUpdater : public QXmlDefaultHandler
{
public:
    GameXmlUpdater(BaseballGame* game, BaseballTeam* awayTeam, BaseballTeam* homeTeam);

    bool startElement(const QString &namespaceURI, const QString &localName,
                      const QString &qName, const QXmlAttributes &atts);
    bool endElement(const QString &namespaceURI, const QString &localName,
                    const QString &qName);
    bool characters(const QString &str);
    bool fatalError(const QXmlParseException &exception);

private:
    BaseballTeam* awayTeam;
    BaseballTeam* homeTeam;
    BaseballGame* game;
    BaseballPlayer* curPlayer;

    bool inTotals, inPlayer, inAwayTeam;
};

#endif // GAMEXMLUPDATER_H
