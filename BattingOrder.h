#ifndef BATTINGORDER_H
#define BATTINGORDER_H

#include <QGraphicsRectItem>
#include "BaseballGame.h"
#include "graphic.h"
class BattingOrder : public Graphic, public QGraphicsRectItem
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
    QLinearGradient homeGradient, awayGradient, mainGradient;
    QFont font;
    QString homeName, awayName;
};

#endif // BATTINGORDER_H
