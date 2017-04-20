#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsScene>
#include <QMainWindow>
#include "BaseballGame.h"
#include "ControlPanel.h"

#include "CommercialGraphic.h"

#include "PlayerEditor.h"
#include "TeamEditor.h"
#include "LowerThirdCreator.h"
#include "PitcherGraphic.h"
#include "DefenseGraphic.h"
#include "BattingOrder.h"
#include "schedulegraphic.h"
#include "schedulegui.h"
#include "graphic.h"
#include "LineScore.h"
#include "StandingsWidget.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(BaseballGame* game, CommercialGraphic* comGraphic, PitcherGraphic* pg, DefenseGraphic* dg, BattingOrder* bog, LineScore* lineScore, StandingsGraphic* sg);
    ~MainWindow();

    void attachScheduleGraphic(ScheduleGraphic* pSched);
    void makeMenu(BaseballGame* game);
    void attachGraphicToHide(Graphic* graphic);

private:
    ControlPanel panel;

    PlayerEditor awayPlayerEdit, homePlayerEdit;
    TeamEditor awayEdit, homeEdit;
    LowerThirdCreator ltCreator;
    ScheduleGUI scheduleGui;
    StandingsWidget standings;
};

#endif // MAINWINDOW_H
