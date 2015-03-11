#ifndef PITCHERS_H
#define PITCHERS_H

#include <QWidget>
#include "BaseballGame.h"
#include <QComboBox>
#include <QPushButton>

class Pitchers : public QWidget {
    Q_OBJECT
public:
    Pitchers(BaseballGame* game);

signals:
    void requestHomeLt(int player);
    void requestAwayLt(int player);
    void requestHomeSb(int player);
    void requestAwaySb(int player);

private slots:
    void getHomeLt();
    void getAwayLt();
    void getHomeSb();
    void getAwaySb();

private:
    QComboBox homePitcher, awayPitcher;
    QPushButton awayLt, awaySB, homeLt, homeSB, awaySeason, homeSeason;

};

#endif // PITCHERS_H
