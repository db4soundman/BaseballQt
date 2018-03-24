#include "PitcherGraphic.h"
#include <QGraphicsScene>
#include "MiamiAllAccessBaseball.h"
#define GRADIENT_LEVEL .5
#define WIDTH 350
#define HEIGHT 517
#define NAME_HEIGHT 30

PitcherGraphic::PitcherGraphic(BaseballGame *game) : font(QFont("Arial",24, QFont::Bold))
{

    setRect(0,0,WIDTH, HEIGHT);
    homeTeam = true;
    show = false;
    awayGradient.setStart(0,0);
    awayGradient.setFinalStop(0,NAME_HEIGHT);
    homeGradient.setStart(0,0);
    homeGradient.setFinalStop(0,NAME_HEIGHT);
    mainGradient.setStart(0,NAME_HEIGHT);
    mainGradient.setFinalStop(0, HEIGHT);
    homeStatGradient.setStart(0,NAME_HEIGHT);
    homeStatGradient.setFinalStop(0, HEIGHT);
    awayStatGradient.setStart(0,NAME_HEIGHT);
    awayStatGradient.setFinalStop(0, HEIGHT);
    nameFont = font;
    this->game=game;
    connect(game->getAwayTeam(), SIGNAL(pitcherChanged(int)), this, SLOT(setAwayPitcher(int)));
    connect(game->getHomeTeam(), SIGNAL(pitcherChanged(int)), this, SLOT(setHomePitcher(int)));
    prepareColor();
}

void PitcherGraphic::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (show) {
        BaseballPlayer player = homeTeam? homePitcher : awayPitcher;
        painter->setFont(font);
        painter->fillRect(0,0,WIDTH,NAME_HEIGHT, homeTeam? homeGradient : awayGradient);
        painter->fillRect(0,NAME_HEIGHT, WIDTH, HEIGHT - NAME_HEIGHT, homeTeam? homeStatGradient : awayStatGradient);
        painter->setPen(QColor(255,255,255));
        painter->drawText(0,0, 48, NAME_HEIGHT, Qt::AlignCenter, player.getUni());
        painter->setFont(nameFont);
        painter->drawText(48,0, WIDTH - 48, NAME_HEIGHT, Qt::AlignCenter, player.getName());
        painter->setFont(font);
        painter->drawText(15, 42* 1, 240, 30, Qt::AlignLeft, "APP");
        painter->drawText(15,  42* 2, 240, 30, Qt::AlignLeft, "GS/SV");
        painter->drawText(15,  42* 3, 240, 30, Qt::AlignLeft, "W-L");
        painter->drawText(15,  42* 4, 240, 30, Qt::AlignLeft, "ERA");
        painter->drawText(15,  42* 5, 240, 30, Qt::AlignLeft, "IP");
        painter->drawText(15,  42* 6, 240, 30, Qt::AlignLeft, "H");
        painter->drawText(15,  42* 7, 240, 30, Qt::AlignLeft, "R");
        painter->drawText(15,  42* 8, 240, 30, Qt::AlignLeft, "ER");
        painter->drawText(15,  42* 9, 240, 30, Qt::AlignLeft, "BB");
        painter->drawText(15,  42* 10, 240, 30, Qt::AlignLeft, "SO");

        painter->drawText(105,  42* 1, 240, 30, Qt::AlignRight, QString::number(player.getAp()));
        painter->drawText(105,  42* 2, 240, 30, Qt::AlignRight,  QString::number(player.getGs()) + "/" +  QString::number(player.getSaves()));
        painter->drawText(105,  42* 3, 240, 30, Qt::AlignRight,  QString::number(player.getWins()) + "-" +  QString::number(player.getLosses()));
        painter->drawText(105,  42* 4, 240, 30, Qt::AlignRight,  player.getEra());
        painter->drawText(105,  42* 5, 240, 30, Qt::AlignRight,  player.getIp());
        painter->drawText(105,  42* 6, 240, 30, Qt::AlignRight,  QString::number(player.getHitsAllowed()));
        painter->drawText(105,  42* 7, 240, 30, Qt::AlignRight,  QString::number(player.getRunsAllowed()));
        painter->drawText(105,  42* 8, 240, 30, Qt::AlignRight,  QString::number(player.getEr()));
        painter->drawText(105,  42* 9, 240, 30, Qt::AlignRight, QString::number(player.getBb()));
        painter->drawText(105,  42* 10, 240, 30, Qt::AlignRight,  QString::number(player.getKOut()));
    }
}

void PitcherGraphic::setAwayPitcher(int idx)
{
    awayPitcher = game->getAwayTeam()->getPlayer(idx);
}

void PitcherGraphic::setHomePitcher(int idx)
{
    homePitcher = game->getHomeTeam()->getPlayer(idx);
}

void PitcherGraphic::displayGraphic(bool team)
{
    homeTeam = team;
    show = true;
    nameFont.setPointSize(24);
    prepareFontSize();
    scene()->update(x(),y(),WIDTH,HEIGHT);
}

void PitcherGraphic::hideGraphic()
{
    if (show) {
        show =false;
        scene()->update(x(),y(),WIDTH,HEIGHT);
    }
}

void PitcherGraphic::prepareColor()
{
    QColor homeColor = MiamiAllAccessBaseball::homeSchool.getPrimaryColor();
    QColor awayColor = MiamiAllAccessBaseball::awaySchool.getPrimaryColor();
    int red, green, blue;
    red = -1*homeColor.red() *GRADIENT_LEVEL + homeColor.red();
    green = -1*homeColor.green() *GRADIENT_LEVEL + homeColor.green();
    blue = -1*homeColor.blue() *GRADIENT_LEVEL + homeColor.blue();

    QColor end(red, green, blue);
    if (end == QColor(0,0,0))
        end = QColor(1,1,1);
    homeGradient.setColorAt(0, homeColor);
    homeGradient.setColorAt(1, end);
    homeStatGradient.setColorAt(0, homeColor);
    homeStatGradient.setColorAt(1, end);


    red = -1*awayColor.red() *GRADIENT_LEVEL + awayColor.red();
    green = -1*awayColor.green() *GRADIENT_LEVEL + awayColor.green();
    blue = -1*awayColor.blue() *GRADIENT_LEVEL + awayColor.blue();
    QColor end2(red, green, blue);
    if (end2 == QColor(0,0,0))
        end2 = QColor(1,1,1);
    awayGradient.setColorAt(0, awayColor);
    awayGradient.setColorAt(1, end2);
    awayStatGradient.setColorAt(0, awayColor);
    awayStatGradient.setColorAt(1, end2);


    mainGradient.setColorAt(0, QColor(25,25,25));
    mainGradient.setColorAt(.5, QColor(83,83,83));
    mainGradient.setColorAt(1, QColor(25,25,25));
}

void
PitcherGraphic::prepareFontSize() {
    int subtraction = 1;
    QFontMetrics fontSize(nameFont);
    BaseballPlayer player = homeTeam? homePitcher : awayPitcher;
    while (fontSize.width(player.getName()) > WIDTH - 58) {
        QFont tempFont("Arial", 24 - subtraction, QFont::Bold);
        //nameFont.setPointSize(fontPointSize - subtraction);
        subtraction++;
        nameFont = tempFont;
        QFontMetrics temp(nameFont);
        fontSize = temp;
    }
}
