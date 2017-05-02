#include "StandingsEntry.h"

StandingsEntry::StandingsEntry(QString name, int pWins, int pLosses, int pOvrWins, int pOvrLosses) {
    teamName = name;
    wins = pWins;
    losses = pLosses;
    ovrWins = pOvrWins;
    ovrLosses = pOvrLosses;
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

int StandingsEntry::getOvrWins() const
{
    return ovrWins;
}

void StandingsEntry::setOvrWins(int value)
{
    ovrWins = value;
}

int StandingsEntry::getOvrLosses() const
{
    return ovrLosses;
}

void StandingsEntry::setOvrLosses(int value)
{
    ovrLosses = value;
}





