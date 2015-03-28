#include "StatDisplayControls.h"

StatDisplayControls::StatDisplayControls(BaseballGame* game, PitcherGraphic *pg) :
    homeStats(game, true), awayStats(game, false),  pitchers(game, pg), batters(game), preStats(game) {
    addTab(&pitchers, "Pitchers");
    addTab(&batters, "Batters");
    addTab(&awayStats, game->getAwayName());
    addTab(&homeStats, game->getHomeName());
}
