#include "StandingsEntry.h"

StandingsEntry::StandingsEntry(QString name, int pWins, int pLosses, int pTies, int pShootoutWins) {
    teamName = name;
    wins = pWins;
    losses = pLosses;
    ties = pTies;
    shootoutWins = pShootoutWins;
    setPoints();
}

QString StandingsEntry::getTeamName() const
{
    return teamName;
}

void StandingsEntry::setTeamName(const QString& value)
{
    teamName = value;
}
int StandingsEntry::getWins() const
{
    return wins;
}

void StandingsEntry::setWins(int value)
{
    wins = value;
}
int StandingsEntry::getLosses() const
{
    return losses;
}

void StandingsEntry::setLosses(int value)
{
    losses = value;
}
int StandingsEntry::getTies() const
{
    return ties;
}

void StandingsEntry::setTies(int value)
{
    ties = value;
}
int StandingsEntry::getShootoutWins() const
{
    return shootoutWins;
}

void StandingsEntry::setShootoutWins(int value)
{
    shootoutWins = value;
}
int StandingsEntry::getPoints() const
{
    return points;
}

void StandingsEntry::setPoints()
{
    points = wins*3 + ties + shootoutWins;
}






