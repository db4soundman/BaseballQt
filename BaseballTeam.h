#ifndef BASEBALLTEAM_H
#define BASEBALLTEAM_H

#include <QObject>
#include <QList>
#include "BaseballPlayer.h"

class BaseballTeam : public QObject {
    Q_OBJECT
public:
    BaseballTeam();
    BaseballPlayer& getPlayer(const int i);
    BaseballPlayer &getPlayerByNumber(const QString i);
    void addPlayer(BaseballPlayer player);


    QList<QString> getGuiNames();

    BaseballPlayer& getPitcher();
    BaseballPlayer &getBatterByIndex(int index);
    QString getPlayerPos(int orderIndex);

    QList<QString> getOrderDefense() const;
    void setOrderDefense(const QList<QString> &value);

    QList<BaseballPlayer> getRoster() const;
    void setRoster(const QList<BaseballPlayer> &value);

    QList<int> getBattingOrder() const;
    QList<BaseballPlayer> getDefense() const;
    void resetPlayers();

signals:
    void defenseChanged();
    void battingOrderChanged();
    void pitcherChanged(int pitcher);

public slots:

    void setPitcher(int index);
    void setBattingOrder(QList<int>playerIndicies, QList<QString>p);
    void setDefense(QList<int> playerIndicies);

private:
    QList<BaseballPlayer> roster, defense;
    QList<int> battingOrder;
    QList<QString> orderDefense;

    int pitcher;
};

#endif // BASEBALLTEAM_H
