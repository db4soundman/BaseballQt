#ifndef PITCHERGRAPHIC_H
#define PITCHERGRAPHIC_H

#include <QObject>
#include <QGraphicsRectItem>
#include "BaseballGame.h"

class PitcherGraphic : public QObject, public QGraphicsRectItem
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
    void prepareFontSize();
    QColor awayColor, homeColor;
    QLinearGradient homeGradient, homeStatGradient, awayGradient, awayStatGradient, mainGradient;
    QFont font, nameFont;
};

#endif // PITCHERGRAPHIC_H
