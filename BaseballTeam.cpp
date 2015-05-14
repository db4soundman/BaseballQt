#include "BaseballTeam.h"

BaseballTeam::BaseballTeam() {


}

BaseballPlayer* BaseballTeam::getPlayer(const int i) {
    if (i >= roster.size())
        return NULL;
    return roster.at(i);
}

BaseballPlayer*BaseballTeam::getPlayerByNumber(const QString num)
{
    for (int i = 0; i < roster.size(); i++) {
        if (roster.at(i)->getUni() == num) {
            return roster.at(i);
        }
    }
    return NULL;
}

void
BaseballTeam::addPlayer(BaseballPlayer* player) {
    roster.append(player);
}



BaseballPlayer* BaseballTeam::getPitcher()
{
    return pitcher;
}

BaseballPlayer *BaseballTeam::getBatterByIndex(int index)
{
    if (index > 8) return NULL;
    return battingOrder.at(index);
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
        pitcher = getPlayer(index);
        if (defense.size() > 0)
            defense[0] = pitcher;
        else defense.append(pitcher);
        emit pitcherChanged(pitcher);
        emit defenseChanged();
    }
}

void BaseballTeam::setBattingOrder(QList<int> playerIndicies, QList<QString> p)
{
    battingOrder.clear();
    for (int i = 0; i < playerIndicies.length(); i++) {
        battingOrder.append(getPlayer(playerIndicies.at(i)));
        getPlayer(playerIndicies.at(i))->setPos(p.at(i));
    }
    orderDefense = p;
    emit battingOrderChanged();
}

void BaseballTeam::setDefense(QList<int> playerIndicies)
{
    defense.clear();
    defense.append(pitcher);
    // DH used
    if (Q_LIKELY(pitcher != getPlayer(playerIndicies.at(0))))
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
QList<BaseballPlayer *> BaseballTeam::getRoster() const
{
    return roster;
}

void BaseballTeam::setRoster(const QList<BaseballPlayer *> &value)
{
    roster = value;
}

QList<BaseballPlayer *> BaseballTeam::getBattingOrder() const
{
    return battingOrder;
}

QList<BaseballPlayer *> BaseballTeam::getDefense() const
{
    return defense;
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
        names.append(roster.at(i)->getUni() + " - " +
                     roster.at(i)->getName());
    }

    return names;
}

