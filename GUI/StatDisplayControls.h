#ifndef STATDISPLAYCONTROLS_H
#define STATDISPLAYCONTROLS_H

#include <QTabWidget>
#include "BaseballGame.h"
#include "TeamStatControl.h"
#include "BatterStatControl.h"
#include "Pitchers.h"
#include "PitcherGraphic.h"
#include "PreGame.h"

class StatDisplayControls : public QTabWidget {
    Q_OBJECT
public:
    StatDisplayControls(BaseballGame* game, PitcherGraphic* pg);

private:
    TeamStatControl homeStats, awayStats;
    BatterStatControl batters;
    Pitchers pitchers;
    PreGame preStats;
};

#endif // STATDISPLAYCONTROLS_H
