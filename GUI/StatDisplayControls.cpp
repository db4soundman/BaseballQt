#include "StatDisplayControls.h"

StatDisplayControls::StatDisplayControls(BaseballGame* game, PitcherGraphic *pg, DefenseGraphic *dg, BattingOrder *bog) :
    homeStats(game, true), awayStats(game, false),  pitchers(game, pg), batters(game), preStats(game, dg, bog) {
    addTab(&pitchers, "Pitchers");
    addTab(&batters, "Batters");
    addTab(&awayStats, game->getAwayName());
    addTab(&homeStats, game->getHomeName());
    addTab (&preStats, "Pre-Game");
}
