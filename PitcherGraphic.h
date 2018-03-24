#ifndef PITCHERGRAPHIC_H
#define PITCHERGRAPHIC_H

#include <QObject>
#include <QGraphicsRectItem>
#include "BaseballGame.h"
#include "graphic.h"

class PitcherGraphic : public Graphic, public QGraphicsRectItem
{
    Q_OBJECT
public:
    PitcherGraphic(BaseballGame* game);
    void paint(QPainter * painter,
               const QStyleOptionGraphicsItem * option, QWidget * widget = 0);

public slots:
    void setAwayPitcher(int idx);
    void setHomePitcher(int idx);
    void displayGraphic(bool team);
    void hideGraphic();
private:

    BaseballPlayer awayPitcher, homePitcher;
    bool show, homeTeam;

    void prepareColor();
    void prepareFontSize();
    QLinearGradient homeGradient, homeStatGradient, awayGradient, awayStatGradient, mainGradient;
    QFont font, nameFont;
    BaseballGame* game;
};

#endif // PITCHERGRAPHIC_H
