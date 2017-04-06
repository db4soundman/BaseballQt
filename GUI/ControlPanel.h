#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include <QWidget>
//#include <QGroupBox>
#include "BaseballGame.h"
#include "DisplayControls.h"
#include "AtBatResults.h"
#include "CountControl.h"
#include "ScoreControl.h"
#include "GameInfo.h"
#include "ClockControls.h"
#include "StatDisplayControls.h"
#include "Lineups.h"
#include "CommercialGraphic.h"
#include "BaseControlls.h"
#include "PitcherGraphic.h"
#include "BattingOrder.h"
#include "DefenseGraphic.h"


class ControlPanel : public QWidget {
    Q_OBJECT
public:
    ControlPanel(BaseballGame* game, CommercialGraphic* comGraphic, PitcherGraphic* pg, DefenseGraphic* dg, BattingOrder* bog);

    DisplayControls* getDispControls();

private:
    DisplayControls dispControls;
    AtBatResults atBatResults;
    CountControl count;
    ScoreControl scores;
    GameInfo hud;
    ClockControls clockControls;
    StatDisplayControls stats;
    Lineups lineup;
    BaseControlls bases;
};

#endif // CONTROLPANEL_H
