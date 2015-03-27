#include "PitcherGraphic.h"
#include <QGraphicsScene>
#define GRADIENT_LEVEL .5
PitcherGraphic::PitcherGraphic(BaseballGame *game) : font(QFont("Arial",24, QFont::Bold))
{
    setPixmap(QPixmap(":/images/Pitcher.png"));
    homeTeam = true;
    show = false;
    awayColor = game->getAwayColor();
    homeColor = game->getHomeColor();
    awayGradient.setStart(0,-30);
    awayGradient.setFinalStop(0,0);
    homeGradient.setStart(0,-30);
    homeGradient.setFinalStop(0,0);
}

void PitcherGraphic::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (show) {
        BaseballPlayer* player = homeTeam? homePitcher : awayPitcher;
        painter->setFont(font);
        painter->fillRect(0,-30,pixmap().width(),30, homeTeam? homeGradient : awayGradient);
        painter->fillRect(0,0, pixmap().width(), pixmap().height(), mainGradient);
        painter->setPen(QColor(255,255,255));

        painter->drawText(190, 66 * 1, 240, 30, Qt::AlignLeft, "APP");
        painter->drawText(190, 66 * 2, 240, 30, Qt::AlignLeft, "GS/SV");
        painter->drawText(190, 66 * 3, 240, 30, Qt::AlignLeft, "W-L");
        painter->drawText(190, 66 * 4, 240, 30, Qt::AlignLeft, "ERA");
        painter->drawText(190, 66 * 5, 240, 30, Qt::AlignLeft, "IP");
        painter->drawText(190, 66 * 6, 240, 30, Qt::AlignLeft, "H");
        painter->drawText(190, 66 * 7, 240, 30, Qt::AlignLeft, "R");
        painter->drawText(190, 66 * 8, 240, 30, Qt::AlignLeft, "ER");
        painter->drawText(190, 66 * 9, 240, 30, Qt::AlignLeft, "BB");
        painter->drawText(190, 66 * 10, 240, 30, Qt::AlignLeft, "SO");

        painter->drawText(590, 66 * 1, 240, 30, Qt::AlignRight, QString::number(player->getAp()));
        painter->drawText(590, 66 * 2, 240, 30, Qt::AlignRight,  QString::number(player->getGs()) + "/" +  QString::number(player->getSaves()));
        painter->drawText(590, 66 * 3, 240, 30, Qt::AlignRight,  QString::number(player->getWins()) + "-" +  QString::number(player->getLosses()));
        painter->drawText(590, 66 * 4, 240, 30, Qt::AlignRight,  player->getEra());
        painter->drawText(590, 66 * 5, 240, 30, Qt::AlignRight,  player->getIp());
        painter->drawText(590, 66 * 6, 240, 30, Qt::AlignRight,  QString::number(player->getHitsAllowed()));
        painter->drawText(590, 66 * 7, 240, 30, Qt::AlignRight,  QString::number(player->getRunsAllowed()));
        painter->drawText(590, 66 * 8, 240, 30, Qt::AlignRight,  QString::number(player->getEr()));
        painter->drawText(590, 66 * 9, 240, 30, Qt::AlignRight, QString::number(player->getBb()));
        painter->drawText(590, 66 * 10, 240, 30, Qt::AlignRight,  QString::number(player->getKOut()));
    }
}

void PitcherGraphic::setAwayPitcher(BaseballPlayer *pitcher)
{
    awayPitcher = pitcher;
}

void PitcherGraphic::setHomePitcher(BaseballPlayer *pitcher)
{
    homePitcher = pitcher;
}

void PitcherGraphic::displayGraphic(bool team)
{
    homeTeam = team;
    show = true;
    scene()->update(0,0,1920,1080);
}

void PitcherGraphic::hideGraphic()
{
    if (show) {
        show =false;
        scene()->update(0,0,1920,1080);
    }
}

void PitcherGraphic::prepareColor()
{
    int red, green, blue;
    red = -1*homeColor.red() *GRADIENT_LEVEL + homeColor.red();
    green = -1*homeColor.green() *GRADIENT_LEVEL + homeColor.green();
    blue = -1*homeColor.blue() *GRADIENT_LEVEL + homeColor.blue();

    QColor end(red, green, blue);
    if (end == QColor(0,0,0))
        end = QColor(1,1,1);
    homeGradient.setColorAt(.4, homeColor);
    homeGradient.setColorAt(.6, homeColor);
    homeGradient.setColorAt(1, end);
    homeGradient.setColorAt(0, end);

    red = -1*awayColor.red() *GRADIENT_LEVEL + awayColor.red();
    green = -1*awayColor.green() *GRADIENT_LEVEL + awayColor.green();
    blue = -1*awayColor.blue() *GRADIENT_LEVEL + awayColor.blue();
    QColor end2(red, green, blue);
    if (end2 == QColor(0,0,0))
        end2 = QColor(1,1,1);
    awayGradient.setColorAt(.4, awayColor);
    awayGradient.setColorAt(.6, awayColor);
    awayGradient.setColorAt(1, end2);
    awayGradient.setColorAt(0, end2);

    mainGradient.setColorAt(0, QColor(25,25,25));
    mainGradient.setColorAt(.5, QColor(83,83,83));
    mainGradient.setColorAt(1, QColor(25,25,25));
}

