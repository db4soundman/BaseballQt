#include "StatDisplayControls.h"

StatDisplayControls::StatDisplayControls(BaseballGame* game) :
    homeStats(game, true), awayStats(game, false),  pitchers(game), batters(game) {
    addTab(&pitchers, "Pitchers");
    addTab(&batters, "Batters");
    addTab(&awayStats, game->getAwayName());
    addTab(&homeStats, game->getHomeName());
}
