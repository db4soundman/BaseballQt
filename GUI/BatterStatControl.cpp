#include "BatterStatControl.h"
#include <QHBoxLayout>

BatterStatControl::BatterStatControl(BaseballGame* game) {
    displayLt.setText("Show as Lower Third");
    displayBar.setText("Show on Stat Bar");

    QHBoxLayout* main = new QHBoxLayout();
    main->addWidget(&currentBatter);
    main->addWidget(&displayLt);
    main->addWidget(&displayBar);

    connect(&displayLt, SIGNAL(clicked()), this, SLOT(requestLt()));
    connect(&displayBar, SIGNAL(clicked()), this, SLOT(requestSb()));

    connect(this, SIGNAL(requestLt(int)), game, SLOT(gatherAwayStatsLt(int)));
    connect(this, SIGNAL(requestSb(int)), game, SLOT(gatherAwayGameStatsSb(int)));

    // CONNECT GAME TO LABEL SO THAT BATTER TEXT IS CORRECT..................................................................................

    setLayout(main);
}
// FIX THESE SLOTS ..........................................................................................................................
void BatterStatControl::requestLt()
{
    //emit requestLt(playerSelector.currentIndex());
}

void BatterStatControl::requestSb()
{
    //emit requestSb(playerSelector.currentIndex());
}

void BatterStatControl::updateBatterLabel(QString player)
{
    currentBatter.setText("Now Batting: " + player);
}
