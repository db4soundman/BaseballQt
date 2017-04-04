#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QObject>
#include <QPainter>
#include <QColor>
#include <QTimer>
#include <QList>
#include "Clock.h"
#include <QString>

class Scoreboard : public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
     Scoreboard(QColor awayCol, QColor homeCol, QString awayTeam, QString homeTeam,
                 QString sponsorText, QString pAwayRank, QString pHomeRank, QPixmap pawayLogo);
     void paint(QPainter * painter,
                const QStyleOptionGraphicsItem * option, QWidget * widget = 0);

     bool getUseTransparency() const;
     void setUseTransparency(bool value);
     int getRealWidth();

signals:
     void sceneUpdated(int x, int y, int w, int h);
     void transparentField(int x, int y, int w, int h);
     void removeTransparentField(int x, int y, int w, int h);
     void addNoTransparencyZone(QRect r);
     void removeNoTransparencyZone(QRect r);

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
     void updateCount(int b, int s,int o);
     void updateBases();
     void clearBases();
     void delayed();
     void displayClock();
     void displaySponsor();
     void toggleFirstBase(bool on);
     void toggleSecondBase(bool on);
     void toggleThirdBase(bool on);

private:
     QPixmap* homeLogo, *awayLogo;
     //QPixmap emptyBase, filledBase;
     QPixmap watermark;
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

     void updateCount(int b, int s);
     void updateOut(int o);
     void prepareColor();
     void prepareAwayName();
     Clock* clock;
     QFont defaultSponsorText;
     int homeRankOffset, awayRankOffset, homeLogoOffset, awayLogoHeightOffset,awayLogoWidthOffset, out;

};

#endif
