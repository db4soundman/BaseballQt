#include "StatCrewScanner.h"
#include <QFile>
StatCrewScanner::StatCrewScanner(BaseballGame* game, QString fileName)
{
    statCrew = new GameXmlUpdater(game, game->getAwayTeam(), game->getHomeTeam());
    trigger = new QTimer();
    statFile = fileName;
    trigger->setInterval(10000);
    isActive = false;
    connect(trigger, SIGNAL(timeout()), this, SLOT(updateStats()));
    connect(game, SIGNAL(periodChanged(int)), this, SLOT(toggleScanner(int)));
}

void StatCrewScanner::toggleScanner() {
    if (!isActive) {
        trigger->start();
    }
    else {
        trigger->stop();
    }
}

void StatCrewScanner::toggleScanner(int pd)
{
    if (pd == 0) {
        trigger->stop();
        isActive = false;
    }
    else if (pd == 1) {
        trigger->start();
        isActive = true;
    }
}

void StatCrewScanner::updateStats() {
    QFile file(statFile);
    QXmlSimpleReader r;
    r.setContentHandler(statCrew);
    r.setErrorHandler(statCrew);
    QXmlInputSource src(&file);
    r.parse(src);
}
