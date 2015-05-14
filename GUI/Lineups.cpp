#include "Lineups.h"
#include <QGridLayout>
Lineups::Lineups(BaseballGame *game)
{
    QStringList positions;
    positions.append(" P");
    positions.append(" C");
    positions.append("1B");
    positions.append("2B");
    positions.append("SS");
    positions.append("3B");
    positions.append("LF");
    positions.append("CF");
    positions.append("RF");
    positions.append("DH");
    positions.append("PH");
    positions.append("PR");

    QGridLayout* myLayout = new QGridLayout();

    // Away team;
    for (int i = 0; i < 9; i++) {
        QComboBox* box = new QComboBox();
        box->addItems(game->getAwayTeam()->getGuiNames());
        connect(box, SIGNAL(currentIndexChanged(int)), this, SLOT(awayLineupChanged()));
        awayOrder.append(box);
        myLayout->addWidget(box, i, 0);
    }
    for (int i = 0; i < 9; i++) {
        QComboBox* box = new QComboBox();
        box->addItems(positions);
        connect(box, SIGNAL(currentIndexChanged(int)), this, SLOT(awayLineupChanged()));
        awayDef.append(box);
        myLayout->addWidget(box, i, 1);
    }

    // Home team
    for (int i = 0; i < 9; i++) {
        QComboBox* box = new QComboBox();
        box->addItems(game->getHomeTeam()->getGuiNames());
        connect(box, SIGNAL(currentIndexChanged(int)), this, SLOT(homeLineupChanged()));
        homeOrder.append(box);
        myLayout->addWidget(box, i, 2);
    }
    for (int i = 0; i < 9; i++) {
        QComboBox* box = new QComboBox();
        box->addItems(positions);
        connect(box, SIGNAL(currentIndexChanged(int)), this, SLOT(homeLineupChanged()));
        homeDef.append(box);
        myLayout->addWidget(box, i, 3);
    }
    connect(this, SIGNAL(awayDefenseUpdate(QList<int>)), game->getAwayTeam(), SLOT(setDefense(QList<int>)));
    connect(game->getAwayTeam(), SIGNAL(pitcherChanged(BaseballPlayer*)), this, SLOT(awayLineupChanged()));
    connect(this, SIGNAL(awayBattingOrderUpdate(QList<int>,QList<QString>)), game->getAwayTeam(), SLOT(setBattingOrder(QList<int>,QList<QString>)));
    connect(this, SIGNAL(homeBattingOrderUpdate(QList<int>,QList<QString>)), game->getHomeTeam(), SLOT(setBattingOrder(QList<int>,QList<QString>)));
    connect(this, SIGNAL(homeDefenseUpdate(QList<int>)), game->getHomeTeam(), SLOT(setDefense(QList<int>)));
    connect(game->getHomeTeam(), SIGNAL(pitcherChanged(BaseballPlayer*)), this, SLOT(homeLineupChanged()));
    setLayout(myLayout);
    homeLineupChanged();
    awayLineupChanged();
}

void Lineups::awayLineupChanged()
{
    QList <int> def, bat;
    QList<QString> batPos;
    for (int i = 0; i < awayOrder.size(); i++) {
        bat.append(awayOrder.at(i)->currentIndex());
        batPos.append(awayDef.at(i)->currentText());
    }
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < awayDef.size(); j++) {
            if (awayDef.at(j)->currentIndex() == i) {
                def.append(awayOrder.at(j)->currentIndex());
            }
        }
    }
    emit awayBattingOrderUpdate(bat, batPos);
    emit awayDefenseUpdate(def);
}

void Lineups::homeLineupChanged()
{
    QList <int> def, bat;
    QList<QString> batPos;
    for (int i = 0; i < homeOrder.size(); i++) {
        bat.append(homeOrder.at(i)->currentIndex());
        batPos.append(homeDef.at(i)->currentText());
    }
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < homeDef.size(); j++) {
            if (homeDef.at(j)->currentIndex() == i) {
                def.append(homeOrder.at(j)->currentIndex());
            }
        }
    }
    emit homeBattingOrderUpdate(bat, batPos);
    emit homeDefenseUpdate(def);
}
