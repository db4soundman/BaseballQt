#include "GameInfo.h"
#include <QGridLayout>

GameInfo::GameInfo(BaseballGame* game) {
    QGridLayout* main = new QGridLayout();
    awayTeamName.setText(game->getAwayName());
    main->addWidget(&awayTeamName, 0, 0);
    homeTeamName.setText(game->getHomeName());
    main->addWidget(&homeTeamName, 1, 0);
    awayTeamScore.setText("0");
    ah.setText("0");
    ae.setText("0");
    main->addWidget(&awayTeamScore, 0, 1);
    main->addWidget(&ah, 0,2 );
    main->addWidget(&ae, 0, 3);
    homeTeamScore.setText("0");
    hh.setText("0");
    he.setText("0");
    main->addWidget(&homeTeamScore, 1, 1);
    main->addWidget(&hh, 1, 2);
    main->addWidget(&he, 1, 3);
    pd.setText("Not Started");
    main->addWidget(&pd, 2, 0);
   // clock = game->getGameClock();
    time.setText("0-0 0 Out");
    main->addWidget(&time, 2, 1);

    //connect(clock, SIGNAL(clockUpdated()), this, SLOT(updateTime()));
    connect(game, SIGNAL(awayScoreChanged(int)), this, SLOT(updateAwayScore(int)));
    connect(game, SIGNAL(homeScoreChanged(int)), this, SLOT(updateHomeScore(int)));
    connect(game, SIGNAL(periodChanged(QString,int)), this, SLOT(updatePeriod(QString,int)));
    connect(game, SIGNAL(updateCount(int,int,int)), this, SLOT(updateCount(int,int,int)));
    connect(game, SIGNAL(awayHitsChanged(int)), this, SLOT(updateAwayHits(int)));
    connect(game, SIGNAL(awayErrorsChanged(int)), this, SLOT(updateAwayErrors(int)));
    connect(game, SIGNAL(homeHitsChanged(int)), this, SLOT(updateHomeHits(int)));
    connect(game, SIGNAL(homeErrorsChanged(int)), this, SLOT(updateHomeErrors(int)));
    setLayout(main);
}

void
GameInfo::updateCount(int b, int s, int o) {
   time.setText(QString::number(b)+"-"+QString::number(s)+ " "+QString::number(o) + " Out");
}

void GameInfo::updateHomeScore(int score) {
    homeTeamScore.setText(QString::number(score));
}

void GameInfo::updateAwayScore(int score) {
    awayTeamScore.setText(QString::number(score));
}

void GameInfo::updatePeriod(QString mod, int newPd) {
    pd.setText(mod +" " + QString::number(newPd));
}

void GameInfo::updateAwayHits(int h)
{
    ah.setText(QString::number(h));
}

void GameInfo::updateHomeHits(int h)
{
    hh.setText(QString::number(h));
}

void GameInfo::updateAwayErrors(int e)
{
    ae.setText(QString::number(e));
}

void GameInfo::updateHomeErrors(int e)
{
    he.setText(QString::number(e));
}
