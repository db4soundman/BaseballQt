#include "BaseballTeam.h"
#include <algorithm>
BaseballTeam::BaseballTeam() {
    pitcher=0;

}

BaseballPlayer& BaseballTeam::getPlayer(const int i) {
    if (i >= roster.size())
        return roster.last();
    return roster[i];
}

BaseballPlayer& BaseballTeam::getPlayerByNumber(const QString num)
{
    for (int i = 0; i < roster.size(); i++) {
        if (roster.at(i).getUni() == num) {
            return roster[i];
        }
    }
    return roster.last();
}

void
BaseballTeam::addPlayer(BaseballPlayer player) {
    roster.append(player);
    std::sort(roster.begin(), roster.end());
}



BaseballPlayer &BaseballTeam::getPitcher()
{
    return roster[pitcher];
}

BaseballPlayer &BaseballTeam::getBatterByIndex(int index)
{
    if (index > 8) return roster.last();
    return getPlayer(battingOrder[index]);
}

QString BaseballTeam::getPlayerPos(int orderIndex)
{
    return orderDefense.at(orderIndex);
}

void BaseballTeam::setPitcher(int index)
{
    if (index >= roster.size()) {
    }
    else {
        pitcher = index;
        if (defense.size() > 0)
            defense[0] = getPlayer(index);
        else defense.append(getPlayer(index));
        emit pitcherChanged(pitcher);
    }
}

void BaseballTeam::setBattingOrder(QList<int> playerIndicies, QList<QString> p)
{
    battingOrder.clear();
    battingOrder = playerIndicies;
    orderDefense = p;
    for (int i = 0 ; i < battingOrder.size(); i++) {
        getBatterByIndex(i).setPos(orderDefense[i]);
    }
    emit battingOrderChanged();
}

void BaseballTeam::setDefense(QList<int> playerIndicies)
{
    defense.clear();
    defense.append(getPlayer(pitcher));
    // DH used
    if (Q_LIKELY(getPlayer(pitcher) != getPlayer(playerIndicies.at(0))))
        for (int i = 0; i < playerIndicies.size(); i++) {
            defense.append(getPlayer(playerIndicies.at(i)));
        }
    // Pitcher is batting
    else {
        defense.clear();
        for (int i = 0; i < playerIndicies.size(); i++) {
            defense.append(getPlayer(playerIndicies.at(i)));
        }
    }

    emit defenseChanged();
}
QList<BaseballPlayer> BaseballTeam::getRoster() const
{
    return roster;
}

void BaseballTeam::setRoster(const QList<BaseballPlayer> &value)
{
    roster = value;
}

QList<int> BaseballTeam::getBattingOrder() const
{
    return battingOrder;
}

QList<BaseballPlayer> BaseballTeam::getDefense() const
{
    return defense;
}

void BaseballTeam::resetPlayers()
{
    for (int i = 0; i < roster.size() - 1; i++) {
        roster[i].reset();
    }
}

QList<QString> BaseballTeam::getOrderDefense() const
{
    return orderDefense;
}

void BaseballTeam::setOrderDefense(const QList<QString> &value)
{
    orderDefense = value;
}


QList<QString> BaseballTeam::getGuiNames()
{
    QList<QString> names;
    for (int i = 0; i < roster.size(); i++) {
        names.append(roster.at(i).getUni() + " - " +
                     roster.at(i).getName());
    }

    return names;
}

