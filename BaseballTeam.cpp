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

void BaseballTeam::setPitcher(int index)
{
    if (index >= roster.size()) {
    }
    else {
        pitcher = getPlayer(index);
        defense[0] = pitcher;
    }
}

void BaseballTeam::setBattingOrder(QList<int> playerIndicies)
{
    battingOrder.clear();
    for (int i = 0; i < playerIndicies.length(); i++) {
        battingOrder.insert(i,getPlayer(playerIndicies.at(i)));
    }
}

void BaseballTeam::setDefense(QList<int> playerIndicies)
{
    defense.clear();
    defense.insert(0, pitcher);
    for (int i = 0; i < playerIndicies.size(); i++) {
        defense.insert(i + 1, getPlayer(playerIndicies.at(i)));
    }
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

