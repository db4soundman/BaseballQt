#include "BatterStatControl.h"
#include <QHBoxLayout>

BatterStatControl::BatterStatControl(BaseballGame* game) {
    displayLt.setText("Show as Lower Third");
    displayBar.setText("Show on Stat Bar");
    QVBoxLayout* layout = new QVBoxLayout();
    QHBoxLayout* main = new QHBoxLayout();
    main->addWidget(&currentBatter);
    main->addWidget(&displayLt);
    //main->addWidget(&displayBar);

    connect(&displayLt, SIGNAL(clicked()), game, SLOT(gatherBatterGraphic()));
    //connect(&displayBar, SIGNAL(clicked()), this, SLOT(requestSb()));

    //connect(this, SIGNAL(requestLt(int)), game, SLOT(gatherAwayStatsLt(int)));
    //connect(this, SIGNAL(requestSb(int)), game, SLOT(gatherAwayGameStatsSb(int)));


    connect(game, SIGNAL(batterChanged(QString)), this, SLOT(updateBatterLabel(QString)));
    connect(game, SIGNAL(pitchCountUpdate(QString)), this, SLOT(updatePitcherText(QString)));
    layout->addLayout(main);
    layout->addWidget(&currentPitcher);
    setLayout(layout);
}


void BatterStatControl::updateBatterLabel(QString player)
{
    currentBatter.setText("Now Batting: " + player);
}

void BatterStatControl::updatePitcherText(QString pc)
{
    currentPitcher.setText(pc);
}
