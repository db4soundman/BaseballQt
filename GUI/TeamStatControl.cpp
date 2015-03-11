#include "TeamStatControl.h"
#include <QHBoxLayout>

TeamStatControl::TeamStatControl(BaseballGame* game, bool home) {
    playerSelector.addItems(home ? game->getHomeTeam()->getGuiNames() : game->getAwayTeam()->getGuiNames());
    seasonLt.setText("Season Lower Third");
    gameLt.setText("Game Lower Third");
    seasonBar.setText("Season Stat Bar");
    gameBar.setText("Game Stat Bar");

    QHBoxLayout* main = new QHBoxLayout();
    main->addWidget(&playerSelector);
    main->addWidget(&seasonLt);
    main->addWidget(&seasonBar);
    main->addWidget(&gameLt);
    main->addWidget(&gameBar);

    connect(&seasonLt, SIGNAL(clicked()), this, SLOT(requestSeasonLt()));
    connect(&gameLt, SIGNAL(clicked()), this, SLOT(requestGameLt()));
    connect(&seasonBar, SIGNAL(clicked()), this, SLOT(requestSeasonSb()));
    connect(&gameBar, SIGNAL(clicked()), this, SLOT(requestGameSb()));

    if (home) {
        connect(this, SIGNAL(requestSeasonLt(int)), game, SLOT(gatherHomeSeasonStatsLt(int)));
        connect(this, SIGNAL(requestGameLt(int)), game, SLOT(gatherHomeGameStatsLt(int)));
        connect(this, SIGNAL(requestSeasonSb(int)), game, SLOT(gatherHomeSeasonStatsSb(int)));
        connect(this, SIGNAL(requestGameSb(int)), game, SLOT(gatherHomeGameStatsSb(int)));
    }
    else {
        connect(this, SIGNAL(requestSeasonLt(int)), game, SLOT(gatherAwaySeasonStatsLt(int)));
        connect(this, SIGNAL(requestGameLt(int)), game, SLOT(gatherAwayGameStatsLt(int)));
        connect(this, SIGNAL(requestSeasonSb(int)), game, SLOT(gatherAwaySeasonStatsSb(int)));
        connect(this, SIGNAL(requestGameSb(int)), game, SLOT(gatherAwayGameStatsSb(int)));
    }

    setLayout(main);
}

void TeamStatControl::requestSeasonLt()
{
    emit requestSeasonLt(playerSelector.currentIndex());
}

void TeamStatControl::requestGameLt()
{
    emit requestGameLt(playerSelector.currentIndex());
}

void TeamStatControl::requestGameSb()
{
    emit requestGameSb(playerSelector.currentIndex());
}

void TeamStatControl::requestSeasonSb()
{
    emit requestSeasonSb(playerSelector.currentIndex());
}
