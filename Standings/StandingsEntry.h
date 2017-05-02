#ifndef STANDINGSENTRY_H
#define STANDINGSENTRY_H

#include <QString>

class StandingsEntry {
public:
    StandingsEntry(QString name, int pWins, int pLosses, int pOvrWins = 0, int pOvrLosses = 0);

    QString getTeamName() const;
    void setTeamName(const QString& value);

    int getWins() const;
    void setWins(int value);

    int getLosses() const;
    void setLosses(int value);

    int getTies() const;
    void setTies(int value);

    int getOvrWins() const;
    void setOvrWins(int value);

    int getOvrLosses() const;
    void setOvrLosses(int value);

private:
    QString teamName;
    int wins, losses, ties, ovrWins, ovrLosses;

};

#endif // STANDINGSENTRY_H
