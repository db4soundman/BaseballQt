#include "ControlPanel.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>

ControlPanel::ControlPanel(BaseballGame* game, CommercialGraphic* comGraphic) :
    dispControls(game, comGraphic), AtBatResults(game), sogs(game),
    scores(game), hud(game), clockControls(game, comGraphic), stats(game) {
    QHBoxLayout* mainLayout = new QHBoxLayout();

    QVBoxLayout* leftColumn = new QVBoxLayout();
    leftColumn->addWidget(&dispControls);
    QGridLayout* grid = new QGridLayout();
    grid->addWidget(&AtBatResults, 1, 1);
    grid->addWidget(&sogs, 0, 0,Qt::AlignHCenter | Qt::AlignTop);
    grid->addWidget(&scores, 0, 1, Qt::AlignHCenter | Qt::AlignTop );

    leftColumn->addLayout(grid);
    leftColumn->addWidget(&stats);

    QVBoxLayout* rightColumn = new QVBoxLayout();
    rightColumn->addWidget(&hud);
    rightColumn->addWidget(&clockControls);
    rightColumn->addSpacing(125);


    mainLayout->addLayout(leftColumn, 1);
    mainLayout->addLayout(rightColumn);
    setLayout(mainLayout);
}
