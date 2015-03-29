#ifndef PREGAME_H
#define PREGAME_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include "BaseballGame.h"
#include "DefenseGraphic.h"
#include "BattingOrder.h"

class PreGame : public QWidget
{
    Q_OBJECT
public:
    PreGame(BaseballGame* game, DefenseGraphic* dg, BattingOrder* bog);


signals:

public slots:

private:
    QPushButton battingOrder, defenseGraphic;
};

#endif // PREGAME_H
