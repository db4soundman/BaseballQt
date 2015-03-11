#ifndef GAMEINFO_H
#define GAMEINFO_H

#include <QWidget>
#include "BaseballGame.h"
#include <QLabel>

class GameInfo : public QWidget{
    Q_OBJECT
public:
    GameInfo(BaseballGame* game);

signals:

public slots:
    void updateCount(int b, int s, int o);
    void updateHomeScore(int score);
    void updateAwayScore(int score);
    void updatePeriod(QString mod, int newPd);

private:
    QLabel awayTeamName, awayTeamScore, homeTeamName, homeTeamScore, pd, time;
    //Clock* clock;

};

#endif // GAMEINFO_H
