#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QObject>
#include <QPainter>
#include <QColor>
#include <QTimer>
#include <QList>
#include "Clock.h"
#include <QString>

class Scoreboard : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
     Scoreboard(QColor awayCol, QColor homeCol, QString awayTeam, QString homeTeam,
                 QString sponsorText, QString pAwayRank, QString pHomeRank, QString pawayLogo);
     void paint(QPainter * painter,
                const QStyleOptionGraphicsItem * option, QWidget * widget = 0);

     bool getUseTransparency() const;
     void setUseTransparency(bool value);
     int getRealWidth();

signals:
     void sceneUpdated(int x, int y, int w, int h);
     void transparentField(int x, int y, int w, int h);
     void removeTransparentField(int x, int y, int w, int h);

public slots:
     void togglePitchingChange();
     void showPd();
     void final();
     void updateHomeScore(int score);
     void updateAwayScore(int score);
     void updateInning(QString mod, int pd);
     void changeTopBarText(QString text);
     void toggleShowBoard();
     void togglePpClocks();
     void hideBoard();
     void updateClock();
     void updateCount(int b, int s);
     void updateOut(int o);
     void updateBases();
     void clearBases();
     void delayed();
     void displayClock();
     void displaySponsor();
     void toggleFirstBase(bool on);
     void toggleSecondBase(bool on);
     void toggleThirdBase(bool on);

private:
     QPixmap* ppBar;
     QPixmap* topBar;
     QPixmap* homeLogo, *awayLogo;
     QPixmap emptyBase, filledBase;
     QColor homeColor, awayColor;
     QGraphicsTextItem* homeName;
     QGraphicsTextItem* awayName;
     QGraphicsTextItem* homeScore;
     QGraphicsTextItem* awayScore;
     QGraphicsTextItem* topBarText;
     QGraphicsTextItem* awayRank;
     QGraphicsTextItem* homeRank;
     QString ppDescription, inning, centeredTimeText, sponsorText, count;
     QLinearGradient homeGradient, awayGradient, penaltyGradient, mainGradient, clockGradient, ppGradient, scoreGradient;
     bool awayPP, homePP, neutralPP, pitchingChange, sponsor, firstBase, secondBase, thirdBase,
     scoreText, showPP, show, showPdAndClock, showClock, useTransparency, topOfInning;

     void prepareColor();
     void prepareAwayName();
     Clock* clock;
     QFont defaultSponsorText;
     int homeRankOffset, awayRankOffset, homeLogoOffset, awayLogoOffset, out;

};

#endif
