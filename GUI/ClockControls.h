#ifndef CLOCKCONTROLS_H
#define CLOCKCONTROLS_H

#include <QWidget>
#include <QGroupBox>
#include <QPushButton>
#include <QLabel>
#include "BaseballGame.h"
#include "CommercialGraphic.h"

class ClockControls : public QGroupBox {
    Q_OBJECT
public:
    ClockControls(BaseballGame* game, CommercialGraphic* comGraphic);

public slots:
    void updateClockButton(bool clockIsRunning);
    void showClockDialog();

private:
    QLabel label;
    QPushButton advanceBatter, reset, set, nextPd, prevPd, count, intermission, final, pitchingChange;
    Clock* gameClock;
};

#endif // CLOCKCONTROLS_H
