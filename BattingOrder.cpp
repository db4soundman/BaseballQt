#include "BattingOrder.h"
#include <QGraphicsScene>
#define GRADIENT_LEVEL .5
#define COLUMN1_X 5
#define COLUMN2_X 300
#define COLUMN3_X 1150
BattingOrder::BattingOrder(BaseballGame* game) : font(QFont("Arial",24, QFont::Bold))
{
    setPixmap(QPixmap(":/images/Field.png"));
    show = false;
    homeTeam = true;
    awayColor = game->getAwayColor();
    homeColor = game->getHomeColor();
    homeName = game->getHomeName() + " BATTING ORDER";
    awayName = game->getAwayName() + " BATTING ORDER";
    awayGradient.setStart(0,-30);
    awayGradient.setFinalStop(0,0);
    homeGradient.setStart(0,-30);
    homeGradient.setFinalStop(0,0);
    mainGradient.setStart(0,0);
    mainGradient.setFinalStop(0,pixmap().height());
    awayTeam = game->getAwayTeam();
    homeTeamP = game->getHomeTeam();
    prepareColor();
    connect(game->getAwayTeam(), SIGNAL(battingOrderChanged()), this, SLOT(setAwayOrder()));
    connect(game->getHomeTeam(), SIGNAL(battingOrderChanged()), this, SLOT(setHomeOrder()));
}

void BattingOrder::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (show) {
        painter->setFont(font);
        painter->fillRect(0,-30,pixmap().width(),30, homeTeam? homeGradient : awayGradient);
        painter->fillRect(0,0, pixmap().width(), pixmap().height(), mainGradient);
        painter->setPen(QColor(255,255,255));
        painter->drawText(0,-30, pixmap().width(), 30, Qt::AlignCenter,homeTeam? homeName : awayName);
        for (int i = 0; i < 9; i++) {
            painter->drawText(COLUMN1_X, 24 + (24 * (i*2)), 95, 28, Qt::AlignCenter, homeTeam? homePos.at(i) : awayPos.at(i));
            painter->drawText(COLUMN2_X, 24 + (24 * (i*2)), 700, 28, Qt::AlignCenter, homeTeam? home.at(i)->getName() : away.at(i)->getName());
            painter->drawText(COLUMN3_X, 24 + (24 * (i*2)), 140, 28, Qt::AlignCenter, homeTeam? home.at(i)->getAvg() : away.at(i)->getAvg());
        }
    }
}

void BattingOrder::setAwayOrder()
{
    away = awayTeam->getBattingOrder();
    awayPos = awayTeam->getOrderDefense();
}

void BattingOrder::setHomeOrder()
{
    home = homeTeamP->getBattingOrder();
    homePos = homeTeamP->getOrderDefense();
}

void BattingOrder::displayGraphic(bool team)
{
    homeTeam = team;
    show = true;
    scene()->update(0,0,1920,1080);
}

void BattingOrder::hideGraphic()
{
    if (show) {
        show =false;
        scene()->update(0,0,1920,1080);
    }
}
void BattingOrder::prepareColor() {
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


