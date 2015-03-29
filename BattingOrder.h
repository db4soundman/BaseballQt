#ifndef BATTINGORDER_H
#define BATTINGORDER_H

#include <QGraphicsPixmapItem>
#include "BaseballGame.h"
class BattingOrder : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    BattingOrder(BaseballGame* game);

    void paint(QPainter * painter,
               const QStyleOptionGraphicsItem * option, QWidget * widget = 0);

public slots:
    void setAwayOrder();
    void setHomeOrder();
    void displayGraphic(bool team);
    void hideGraphic();
private:
    QList<BaseballPlayer*> away, home;
    QList<QString> awayPos, homePos;
    bool show, homeTeam;
    BaseballTeam* homeTeamP, *awayTeam;
    void prepareColor();
    QColor awayColor, homeColor;
    QLinearGradient homeGradient, awayGradient, mainGradient;
    QFont font;
    QString homeName, awayName;
};

#endif // BATTINGORDER_H
