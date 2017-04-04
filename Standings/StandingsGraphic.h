#ifndef STANDINGSGRAPHIC_H
#define STANDINGSGRAPHIC_H

#include <QGraphicsRectItem>
#include "StandingsEntry.h"
#include <QList>
#include <QPainter>
#include <QPixmap>
#include <QLinearGradient>

class StandingsGraphic : public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    StandingsGraphic(QGraphicsRectItem *parent = 0);

    void paint(QPainter * painter,
               const QStyleOptionGraphicsItem * option, QWidget * widget = 0);

public slots:
    void updateStandings(QList<StandingsEntry> list);
    void toggleShow();
    void hide();

private:
    QList<StandingsEntry> nchcStandings;
    QPixmap nchcLogo;
    QLinearGradient bgGradient, pipe1, pipe2;
    bool show;

    void prepareColor();
};

#endif // STANDINGSGRAPHIC_H
