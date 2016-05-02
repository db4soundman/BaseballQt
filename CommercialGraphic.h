#ifndef COMMERCIALGRAPHIC_H
#define COMMERCIALGRAPHIC_H

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QFont>
#include "BaseballGame.h"
#include <QLinearGradient>
#include <QPainter>
#include <QGraphicsTextItem>

class CommercialGraphic : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    CommercialGraphic(BaseballGame* game, int width, QPixmap pawayLogo, QGraphicsItem *parent = 0);

    void paint(QPainter * painter,
               const QStyleOptionGraphicsItem * option, QWidget * widget = 0);

    QString getMaaText() const;
    void setMaaText(const QString &value);

signals:

public slots:
    void prepareAndShow();
    void updateClock();
    void showClock();
    void intermissionTime();
    void finalTime();
    void hide();

private:
    QPixmap blackBar;
    QLinearGradient homeTeamGradient, awayTeamGradient;
    BaseballGame* baseballGame;
    bool show, inGame;
    QGraphicsTextItem* away, *home;
    QString homeScore, awayScore, maaText, clock, hitsHome, hitsAway, errorsHome, errorsAway;
    QFont descriptiveFont;
    int clockStatus, WIDTH, NAME_WIDTH;
    void checkAwayFont();
    void prepareGradients(QColor awayColor, QColor homeColor);
    QPixmap homeLogo, *awayLogo;
};

#endif // COMMERCIALGRAPHIC_H
