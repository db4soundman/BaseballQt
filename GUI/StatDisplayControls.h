#ifndef STATDISPLAYCONTROLS_H
#define STATDISPLAYCONTROLS_H

#include <QTabWidget>
#include "BaseballGame.h"
#include "GoalDisplayWidget.h"
#include "TeamStatControl.h"
#include "BatterStatControl.h"
#include "Pitchers.h"

class StatDisplayControls : public QTabWidget {
    Q_OBJECT
public:
    StatDisplayControls(BaseballGame* game);

private:
    //GoalDisplayWidget homeGoal, awayGoal;
    TeamStatControl homeStats, awayStats;
    BatterStatControl batters;
    Pitchers pitchers;

};

#endif // STATDISPLAYCONTROLS_H
