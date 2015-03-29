#include "PreGame.h"
#include <QVBoxLayout>
PreGame::PreGame(BaseballGame* game, DefenseGraphic *dg, BattingOrder *bog)
{
    QVBoxLayout* myLayout = new QVBoxLayout();
    defenseGraphic.setText("Defense");
    battingOrder.setText("Batting Order");

    myLayout->addWidget(&defenseGraphic);
    myLayout->addWidget(&battingOrder);

    setLayout(myLayout);

    connect(&defenseGraphic, SIGNAL(clicked()), game, SLOT(decideTeamForDefense()));
    connect(&defenseGraphic, SIGNAL(clicked()), bog, SLOT(hideGraphic()));
    connect(&battingOrder, SIGNAL(clicked()), game, SLOT(decideTeamForBattingOrder()));
    connect(&battingOrder, SIGNAL(clicked()), dg, SLOT(hideGraphic()));
}


