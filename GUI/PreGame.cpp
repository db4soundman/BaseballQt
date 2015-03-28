#include "PreGame.h"
#include <QVBoxLayout>
PreGame::PreGame(BaseballGame* game)
{
    QVBoxLayout* myLayout = new QVBoxLayout();
    defenseGraphic.setText("Defense");
    battingOrder.setText("Batting Order");

    myLayout->addWidget(&defenseGraphic);
    myLayout->addWidget(&battingOrder);

    setLayout(myLayout);

    connect(&defenseGraphic, SIGNAL(clicked()), game, SLOT(decideTeamForDefense()));
    connect(&battingOrder, SIGNAL(clicked()), game, SLOT(decideTeamForBattingOrder()));
}


