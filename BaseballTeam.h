#ifndef BASEBALLTEAM_H
#define BASEBALLTEAM_H

#include <QObject>
#include <QList>
#include "BaseballPlayer.h"

class BaseballTeam : public QObject {
    Q_OBJECT
public:
    BaseballTeam();
    BaseballPlayer* getPlayer(const int i);
    BaseballPlayer* getPlayerByNumber(const QString i);
    void addPlayer(BaseballPlayer* player);


    QList<QString> getGuiNames();

    BaseballPlayer* getPitcher();

signals:


public slots:

    void setPitcher(int index);
    void setBattingOrder(QList<int>playerIndicies);
    void setDefense(QList<int> playerIndicies);

private:
    QList<BaseballPlayer*> roster, battingOrder, defense;

    BaseballPlayer* pitcher;
    // period data???
    // game history???
};

#endif // BASEBALLTEAM_H
