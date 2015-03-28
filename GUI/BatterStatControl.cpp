#include "BatterStatControl.h"
#include <QHBoxLayout>

BatterStatControl::BatterStatControl(BaseballGame* game) {
    displayLt.setText("Show as Lower Third");
    displayBar.setText("Show on Stat Bar");

    QHBoxLayout* main = new QHBoxLayout();
    main->addWidget(&currentBatter);
    main->addWidget(&displayLt);
    //main->addWidget(&displayBar);

    connect(&displayLt, SIGNAL(clicked()), game, SLOT(gatherBatterGraphic()));
    //connect(&displayBar, SIGNAL(clicked()), this, SLOT(requestSb()));

    //connect(this, SIGNAL(requestLt(int)), game, SLOT(gatherAwayStatsLt(int)));
    //connect(this, SIGNAL(requestSb(int)), game, SLOT(gatherAwayGameStatsSb(int)));


    connect(game, SIGNAL(batterChanged(QString)), this, SLOT(updateBatterLabel(QString)));
    setLayout(main);
}


void BatterStatControl::updateBatterLabel(QString player)
{
    currentBatter.setText("Now Batting: " + player);
}
