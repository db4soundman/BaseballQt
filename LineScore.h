#ifndef LINESCORE_H
#define LINESCORE_H

#include "graphic.h"
#include <QGraphicsRectItem>
#include <QLinearGradient>
#include "BaseballGame.h"

class LineScore : public Graphic, public QGraphicsRectItem
{
    Q_OBJECT
public:
    LineScore(BaseballGame* pGame, QPixmap pawayLogo, QObject *parent = 0);

    void paint(QPainter * painter,
               const QStyleOptionGraphicsItem * option, QWidget * widget = 0);


signals:
    void addNoTransparencyZone(QRect r);
    void removeNoTransparencyZone(QRect r);

public slots:
    void prepareAndShow();
    void updateClock();
    void showClock();
    void intermissionTime();
    void finalTime();
    void hideGraphic();

private:
    QPixmap networkLogo;
    QLinearGradient homeTeamGradient, awayTeamGradient, blackGradient;
    BaseballGame* baseballGame;
    bool show, inGame;
    QGraphicsTextItem* away, *home;
    QString homeScore, awayScore, clock, hitsHome, hitsAway, errorsHome, errorsAway;
    QFont descriptiveFont;
    int clockStatus, awayHeightOffset, awayWidthOffset;
    void checkAwayFont();
    void prepareGradients(QColor awayColor, QColor homeColor);
    QPixmap homeLogo, *awayLogo;
};

#endif // LINESCORE_H
