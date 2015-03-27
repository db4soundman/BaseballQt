#ifndef PITCHERGRAPHIC_H
#define PITCHERGRAPHIC_H

#include <QObject>
#include "BaseballGame.h"

class PitcherGraphic : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    PitcherGraphic(BaseballGame* game);
    void paint(QPainter * painter,
               const QStyleOptionGraphicsItem * option, QWidget * widget = 0);

public slots:
    void setAwayPitcher(BaseballPlayer* pitcher);
    void setHomePitcher(BaseballPlayer* pitcher);
    void displayGraphic(bool team);
    void hideGraphic();
private:

    BaseballPlayer *awayPitcher, *homePitcher;
    bool show, homeTeam;

    void prepareColor();
    QColor awayColor, homeColor;
    QLinearGradient homeGradient, awayGradient, mainGradient;
    QFont font;
};

#endif // PITCHERGRAPHIC_H
