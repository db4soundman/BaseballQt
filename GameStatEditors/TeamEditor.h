#ifndef TEAMEDITOR_H
#define TEAMEDITOR_H

#include <QWidget>
#include <QSpinBox>
#include "BaseballTeam.h"

class TeamEditor : public QWidget {
    Q_OBJECT
public:
    TeamEditor(BaseballTeam* pTeam);

public slots:
    void updateSpinBoxes();
    void changeStats();

private:
    BaseballTeam* team;
    QSpinBox ppg, ppopp, pk, pkopp;
    int ppgS, ppoppS, pkS, pkoppS;

};

#endif // TEAMEDITOR_H
