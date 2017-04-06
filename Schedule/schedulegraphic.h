#ifndef SCHEDULEGRAPHIC_H
#define SCHEDULEGRAPHIC_H

#include "scheduleentry.h"
#include <QGraphicsRectItem>
#include <QList>
#include <QPainter>
#include <QLinearGradient>
#include <QPixmap>
#include "graphic.h"

class ScheduleGraphic : public Graphic, public QGraphicsRectItem {
    Q_OBJECT
public:
    ScheduleGraphic(QGraphicsItem* parent = 0);

    void paint(QPainter * painter,
               const QStyleOptionGraphicsItem * option, QWidget * widget = 0);

public slots:
    void showGraphic();
    void hideGraphic();
    void receiveData(QList<ScheduleEntry> sched, bool seriesSched);

private:

    QPixmap &getPixmap(QString logo);

    bool show, seriesMode;
    QLinearGradient border, background;
    QPixmap broadcastLogo, none;
    QList<ScheduleEntry> schedule;
};


#endif // SCHEDULEGRAPHIC_H
