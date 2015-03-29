#ifndef DEFENSEGRAPHIC_H
#define DEFENSEGRAPHIC_H

#include <QGraphicsPixmapItem>
#include "BaseballGame.h"
#include "BaseballPlayer.h"

class DefenseGraphic : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    DefenseGraphic(BaseballGame* game);

    void paint(QPainter * painter,
               const QStyleOptionGraphicsItem * option, QWidget * widget = 0);

public slots:
    void setAwayDef();
    void setHomeDef();
    void displayGraphic(bool team);
    void hideGraphic();
private:
    QList<BaseballPlayer*> away, home;
    bool show, homeTeam;
    BaseballTeam* homeTeamP, *awayTeam;
    void prepareColor();
    QColor awayColor, homeColor;
    QLinearGradient homeGradient, awayGradient;
    QFont font;
    QString homeName, awayName;

};

#endif // DEFENSEGRAPHIC_H
