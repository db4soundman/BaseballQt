#ifndef COMMERCIALGRAPHIC_H
#define COMMERCIALGRAPHIC_H

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QFont>
#include "BaseballGame.h"
#include <QLinearGradient>
#include <QPainter>
#include <QGraphicsTextItem>

class CommercialGraphic : public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    CommercialGraphic(BaseballGame* game, int width, QGraphicsItem *parent = 0);

    void paint(QPainter * painter,
               const QStyleOptionGraphicsItem * option, QWidget * widget = 0);

    QString getMaaText() const;
    void setMaaText(const QString &value);

signals:
    void addNoTransparencyZone(QRect r);
    void removeNoTransparencyZone(QRect r);

public slots:
    void prepareAndShow();
    void updateClock();
    void showClock();
    void intermissionTime();
    void finalTime();
    void hide();

private:
    QPixmap networkLogo;
    QLinearGradient homeTeamGradient, awayTeamGradient, blackGradient;
    BaseballGame* baseballGame;
    bool show;
    QGraphicsTextItem* away, *home;
    QString homeScore, awayScore, maaText, clock, hitsHome, hitsAway, errorsHome, errorsAway;
    QFont descriptiveFont;
    int clockStatus, awayHeightOffset, awayWidthOffset;
    void checkAwayFont();
    void prepareGradients(QColor awayColor, QColor homeColor);
    QPixmap homeLogo, awayLogo;
};

#endif // COMMERCIALGRAPHIC_H
