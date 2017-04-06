#include "ControlPanel.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>

ControlPanel::ControlPanel(BaseballGame* game, CommercialGraphic* comGraphic, PitcherGraphic *pg, DefenseGraphic *dg, BattingOrder *bog) :
    dispControls(game, comGraphic, pg, dg, bog), atBatResults(game), count(game), lineup(game),
    scores(game), hud(game), clockControls(game, comGraphic), stats(game, pg, dg, bog), bases(game) {
    QHBoxLayout* mainLayout = new QHBoxLayout();

    QVBoxLayout* leftColumn = new QVBoxLayout();
    leftColumn->addWidget(&dispControls);
    QGridLayout* grid = new QGridLayout();
    grid->addWidget(&lineup, 0, 0, 3, 1);
    grid->addWidget(&atBatResults, 1, 1);
    grid->addWidget(&count, 0, 1,Qt::AlignHCenter | Qt::AlignTop);
    grid->addWidget(&bases, 1, 2);
    grid->addWidget(&scores, 0, 2, Qt::AlignHCenter | Qt::AlignTop );
    grid->addWidget(&stats, 2, 1, 1, 2);
    leftColumn->addLayout(grid);


    QVBoxLayout* rightColumn = new QVBoxLayout();
    rightColumn->addWidget(&hud);
    rightColumn->addWidget(&clockControls);
    rightColumn->addSpacing(125);


    mainLayout->addLayout(leftColumn, 1);
    mainLayout->addLayout(rightColumn);
    setLayout(mainLayout);
}

DisplayControls *ControlPanel::getDispControls()
{
    return &dispControls;
}
