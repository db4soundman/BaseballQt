#ifndef STANDINGSENTRY_H
#define STANDINGSENTRY_H

#include <QString>

class StandingsEntry {
public:
    StandingsEntry(QString name, int pWins, int pLosses);

    QString getTeamName() const;
    void setTeamName(const QString& value);

    int getWins() const;
    void setWins(int value);

    int getLosses() const;
    void setLosses(int value);

    int getTies() const;
    void setTies(int value);

private:
    QString teamName;
    int wins, losses, ties;

};

#endif // STANDINGSENTRY_H
