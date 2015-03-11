#ifndef PLAYEREDITOR_H
#define PLAYEREDITOR_H

#include <QWidget>
#include <QSpinBox>
#include <QComboBox>
#include "BaseballGame.h"
#include "BaseballPlayer.h"

class PlayerEditor : public QWidget {
    Q_OBJECT
public:
    PlayerEditor(BaseballGame* game, bool homeTeam = false);

public slots:
    void updateSpinBoxes();
    void applyStats();

private slots:
    void changePlayer(int index);

private:
    QSpinBox goalsToday, astToday, penaltiesToday, pimToday;
    QComboBox playerSelect;
    BaseballPlayer* player;
    BaseballTeam* team;

};

#endif // PLAYEREDITOR_H
