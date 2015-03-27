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

void BaseballTeam::setPitcher(int index)
{
    if (index >= roster.size()) {
    }
    else {
        pitcher = getPlayer(index);
        defense[0] = pitcher;
    }
}

void BaseballTeam::setBattingOrder(QList<int> playerIndicies, QList<QString> p)
{
    battingOrder.clear();
    for (int i = 0; i < playerIndicies.length(); i++) {
        battingOrder.insert(i,getPlayer(playerIndicies.at(i)));
    }
    orderDefense = p;
    emit battingOrderChanged(battingOrder, orderDefense);
}

void BaseballTeam::setDefense(QList<int> playerIndicies)
{
    defense.clear();
    defense.insert(0, pitcher);
    // DH used
    if (Q_LIKELY(pitcher != getPlayer(playerIndicies.at(0))))
        for (int i = 0; i < playerIndicies.size(); i++) {
            defense.insert(i + 1, getPlayer(playerIndicies.at(i)));
        }
    // Pitcher is batting
    else {
        for (int i = 0; i < playerIndicies.size(); i++) {
            defense.insert(i, getPlayer(playerIndicies.at(i)));
        }
    }

    emit defenseChanged(defense);
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

