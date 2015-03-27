#ifndef SCORECONTROL_H
#define SCORECONTROL_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include "BaseballGame.h"

class ScoreControl : public QWidget {
     Q_OBJECT
public:
    ScoreControl(BaseballGame* game);

signals:
    void changeScore(int value);

private slots:
    void up1();
    void down1();
    void up2();
    void down2();
    void up3();
    void down3();
    void up4();
    void down4();

private:
    QLabel title;
    QPushButton sm1, sp1, sm2, sp2, sm3, sp3, sm4, sp4,hm1,hp1,em1,ep1;
};

#endif // SCORECONTROL_H
