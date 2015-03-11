#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include <QWidget>
#include "BaseballGame.h"
#include "DisplayControls.h"
#include "AtBatResults.h"
#include "CountControl.h"
#include "ScoreControl.h"
#include "GameInfo.h"
#include "ClockControls.h"
#include "StatDisplayControls.h"

#include "CommercialGraphic.h"



class ControlPanel : public QWidget {
    Q_OBJECT
public:
    ControlPanel(BaseballGame* game, CommercialGraphic* comGraphic);

private:
    DisplayControls dispControls;
    AtBatResults AtBatResults;
    CountControl sogs;
    ScoreControl scores;
    GameInfo hud;
    ClockControls clockControls;
    StatDisplayControls stats;
};

#endif // CONTROLPANEL_H
