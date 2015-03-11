#include "Pitchers.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

Pitchers::Pitchers(BaseballGame* game) {
    QHBoxLayout* main = new QHBoxLayout();
    QVBoxLayout* away = new QVBoxLayout();
    away->addWidget(new QLabel(game->getAwayName()));
    awaySeason.setText("Season");
    homeSeason.setText("Season");
    awayPitcher.addItems(game->getAwayTeam()->getGuiNames());
    awayPitcher.addItem("UNKNOWN");
    away->addWidget(&awayPitcher);
    awayLt.setText("Game Lower Third");
    awaySB.setText("Game Stat Bar");
    away->addWidget(&awaySeason);
    away->addWidget(&awayLt);
    away->addWidget(&awaySB);

    QVBoxLayout* home = new QVBoxLayout();
    home->addWidget(new QLabel(game->getHomeName()));
    homePitcher.addItems(game->getHomeTeam()->getGuiNames());
    homePitcher.addItem("UNKNOWN");
    home->addWidget(&homePitcher);
    homeLt.setText("Game Lower Third");
    homeSB.setText("Game Stat Bar");
    home->addWidget(&homeSeason);
    home->addWidget(&homeLt);
    home->addWidget(&homeSB);

    main->addLayout(away);
    main->addLayout(home);

    setLayout(main);
// HEY DOUG LOOK AT THIS ---------------------------------------------------------------------------

    /*connect(&awayPitcher, SIGNAL(currentIndexChanged(int)),
            game->getAwayTeam(), SLOT(setGoalie(int)));
    connect(&homePitcher, SIGNAL(currentIndexChanged(int)),
            game->getHomeTeam(), SLOT(setGoalie(int))); */
    connect(&homeLt, SIGNAL(clicked()), this, SLOT(getHomeLt()));
    connect(&awayLt, SIGNAL(clicked()), this, SLOT(getAwayLt()));
    connect(&homeSB, SIGNAL(clicked()), this, SLOT(getHomeSb()));
    connect(&awaySB, SIGNAL(clicked()), this, SLOT(getAwaySb()));

    connect(this, SIGNAL(requestAwayLt(int)), game, SLOT(gatherAwayStatsLt(int)));
    connect(this, SIGNAL(requestHomeLt(int)), game, SLOT(gatherHomeGameStatsLt(int)));
    connect(this, SIGNAL(requestAwaySb(int)), game, SLOT(gatherAwayGameStatsSb(int)));
    connect(this, SIGNAL(requestHomeSb(int)), game, SLOT(gatherHomeGameStatsSb(int)));

    emit awayPitcher.currentIndexChanged(0);
    emit homePitcher.currentIndexChanged(0);

}

void Pitchers::getHomeLt()
{
    emit requestHomeLt(homePitcher.currentIndex());
}

void Pitchers::getAwayLt()
{
    emit requestAwayLt(awayPitcher.currentIndex());
}

void Pitchers::getHomeSb()
{
    emit requestHomeSb(homePitcher.currentIndex());
}

void Pitchers::getAwaySb()
{
    emit requestAwaySb(awayPitcher.currentIndex());
}
