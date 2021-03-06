#ifndef PITCHERS_H
#define PITCHERS_H

#include <QWidget>
#include "BaseballGame.h"
#include <QComboBox>
#include <QPushButton>
#include "PitcherGraphic.h"
class Pitchers : public QWidget {
    Q_OBJECT
public:
    Pitchers(BaseballGame* game, PitcherGraphic* pg);

signals:
    void requestHomeLt(int player);
    void requestAwayLt(int player);
    void requestHomeSb(int player);
    void requestAwaySb(int player);
    void pitcherSeason(bool home);

private slots:
    void getHomeLt();
    void getAwayLt();
    void getHomeSb();
    void getAwaySb();
    void getAwayPitcher();
    void getHomePitcher();

private:
    QComboBox homePitcher, awayPitcher;
    QPushButton awayLt, awaySB, homeLt, homeSB, awaySeason, homeSeason;

};

#endif // PITCHERS_H
