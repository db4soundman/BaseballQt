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

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(BaseballGame* game, CommercialGraphic* comGraphic, PitcherGraphic* pg, DefenseGraphic* dg, BattingOrder* bog);
    ~MainWindow();

private:
    ControlPanel panel;

    PlayerEditor awayPlayerEdit, homePlayerEdit;
    TeamEditor awayEdit, homeEdit;
    LowerThirdCreator ltCreator;

    void makeMenu(BaseballGame* game);
};

#endif // MAINWINDOW_H
