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
    BaseballPlayer* getBatterByIndex(int index);

signals:
    void defenseChanged(QList<BaseballPlayer*> def);
    void battingOrderChanged(QList<BaseballPlayer*>ord, QList<QString> defPos);

public slots:

    void setPitcher(int index);
    void setBattingOrder(QList<int>playerIndicies, QList<QString>p);
    void setDefense(QList<int> playerIndicies);

private:
    QList<BaseballPlayer*> roster, battingOrder, defense;
    QList<QString> orderDefense;

    BaseballPlayer* pitcher;
};

#endif // BASEBALLTEAM_H
