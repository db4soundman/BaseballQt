#ifndef SCORECONTROL_H
#define SCORECONTROL_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include "BaseballGame.h"

class ScoreControl : public QWidget {
public:
    ScoreControl(BaseballGame* game);

private:
    QLabel title;
    QPushButton sm1, sp1, sm2, sp2, sm3, sp3, sm4, sp4;
};

#endif // SCORECONTROL_H
