#include "DefenseGraphic.h"
#include <QGraphicsScene>
#define GRADIENT_LEVEL .5
DefenseGraphic::DefenseGraphic(BaseballGame *game) : font(QFont("Arial",24, QFont::Bold))
{
    setPixmap(QPixmap(":/images/Field.png"));
    show = false;
    homeTeam = true;
    awayColor = game->getAwayColor();
    homeColor = game->getHomeColor();
    homeName = game->getHomeName() + " DEFENSE";
    awayName = game->getAwayName() + " DEFENSE";
    awayGradient.setStart(0,0);
    awayGradient.setFinalStop(0,30);
    homeGradient.setStart(0,0);
    homeGradient.setFinalStop(0,30);
    homeTeamP = game->getHomeTeam();
    awayTeam = game->getAwayTeam();
    prepareColor();
    connect(game->getAwayTeam(), SIGNAL(defenseChanged()), this, SLOT(setAwayDef()));
    connect(game->getHomeTeam(), SIGNAL(defenseChanged()), this, SLOT(setHomeDef()));
}

void DefenseGraphic::paint(QPainter *painter,
                           const QStyleOptionGraphicsItem *option,
                           QWidget *widget)
{
    if (show) {
        painter->setFont(font);
        painter->fillRect(0,0,pixmap().width(),30, homeTeam? homeGradient : awayGradient);
        painter->fillRect(0,30, pixmap().width(), pixmap().height(), QColor(1,1,1));
        painter->drawPixmap(0,30, pixmap());
        painter->setPen(QColor(255,255,255));
        painter->drawText(0,0, pixmap().width(), 30, Qt::AlignCenter,homeTeam? homeName : awayName);
        painter->drawText(438,444,400,28, Qt::AlignCenter,homeTeam? home[0]->getLastName() : away[0]->getLastName());
        painter->drawText(438,762,400,28, Qt::AlignCenter,homeTeam? home[1]->getLastName() : away[1]->getLastName());
        painter->drawText(790,380,400,28, Qt::AlignCenter,homeTeam? home[2]->getLastName() : away[2]->getLastName());
        painter->drawText(718,250,400,28, Qt::AlignCenter,homeTeam? home[3]->getLastName() : away[3]->getLastName());
        painter->drawText(638-440,250,400,28, Qt::AlignCenter,homeTeam? home[4]->getLastName() : away[4]->getLastName());
        painter->drawText(190,380,400,28, Qt::AlignCenter,homeTeam? home[5]->getLastName() : away[5]->getLastName());
        painter->drawText(100,126,400,28, Qt::AlignCenter, homeTeam? home[6]->getLastName() : away[6]->getLastName());
        painter->drawText(438,50,400,28, Qt::AlignCenter,homeTeam? home[7]->getLastName() : away[7]->getLastName());
        painter->drawText(800,126,400,28, Qt::AlignCenter, homeTeam? home[8]->getLastName() : away[8]->getLastName());
    }
}

void DefenseGraphic::setAwayDef()
{
    away = awayTeam->getDefense();
}

void DefenseGraphic::setHomeDef()
{
    home=homeTeamP->getDefense();
}

void DefenseGraphic::displayGraphic(bool team)
{
    homeTeam = team;
    show = true;
    scene()->update(x(), y(), pixmap().width(), pixmap().height());
}

void DefenseGraphic::hideGraphic()
{
    if (show) {
        show = false;
        scene()->update();
    }
}

void DefenseGraphic::prepareColor() {
    int red, green, blue;
    red = -1*homeColor.red() *GRADIENT_LEVEL + homeColor.red();
    green = -1*homeColor.green() *GRADIENT_LEVEL + homeColor.green();
    blue = -1*homeColor.blue() *GRADIENT_LEVEL + homeColor.blue();

    QColor end(red, green, blue);
    if (end == QColor(0,0,0))
        end = QColor(1,1,1);
    homeGradient.setColorAt(0, homeColor);
    homeGradient.setColorAt(1, end);


    red = -1*awayColor.red() *GRADIENT_LEVEL + awayColor.red();
    green = -1*awayColor.green() *GRADIENT_LEVEL + awayColor.green();
    blue = -1*awayColor.blue() *GRADIENT_LEVEL + awayColor.blue();
    QColor end2(red, green, blue);
    if (end2 == QColor(0,0,0))
        end2 = QColor(1,1,1);

    awayGradient.setColorAt(0, awayColor);
    awayGradient.setColorAt(1, end2);

}

