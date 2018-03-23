#include "BattingOrder.h"
#include <QGraphicsScene>
#include "MiamiAllAccessBaseball.h"
#define GRADIENT_LEVEL .5
#define COLUMN1_X 5
#define COLUMN2_X 50
#define COLUMN3_X 545
#define WIDTH 600
#define HEIGHT 500
#define NAME_HEIGHT 34
#define NAME_WIDTH WIDTH
BattingOrder::BattingOrder(BaseballGame* game) : font(QFont("Arial",20, QFont::Bold))
{
    setRect(0,0, WIDTH, HEIGHT);
    show = false;
    homeTeam = true;
    homeName = MiamiAllAccessBaseball::homeSchool.getTitle() + " BATTING ORDER";
    awayName = MiamiAllAccessBaseball::awaySchool.getTitle() + " BATTING ORDER";
    awayGradient.setStart(0,0);
    awayGradient.setFinalStop(0,NAME_HEIGHT);
    homeGradient.setStart(0,0);
    homeGradient.setFinalStop(0,NAME_HEIGHT);
    mainGradient.setStart(0,NAME_HEIGHT);
    mainGradient.setFinalStop(0,HEIGHT);
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
        painter->fillRect(0,0,NAME_WIDTH,NAME_HEIGHT, homeTeam? homeGradient : awayGradient);
        painter->fillRect(0,NAME_HEIGHT, WIDTH, HEIGHT - NAME_HEIGHT, mainGradient);
        painter->setPen(QColor(255,255,255));
        painter->drawText(0,0, NAME_WIDTH, NAME_HEIGHT, Qt::AlignCenter,homeTeam? homeName : awayName);
        for (int i = 0; i < 9; i++) {
            painter->drawText(COLUMN1_X, NAME_HEIGHT + 10 + (24 * (i*2)), 45, 28, Qt::AlignCenter, homeTeam? homePos.at(i) : awayPos.at(i));
            painter->drawText(COLUMN2_X, NAME_HEIGHT + 10 + (24 * (i*2)), 476, 28, Qt::AlignCenter, homeTeam? home.at(i)->getName() : away.at(i)->getName());
            painter->drawText(COLUMN3_X, NAME_HEIGHT + 10 + (24 * (i*2)), 50, 28, Qt::AlignCenter, homeTeam? home.at(i)->getAvg() : away.at(i)->getAvg());
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
    QColor homeColor = MiamiAllAccessBaseball::homeSchool.getPrimaryColor();
    QColor awayColor = MiamiAllAccessBaseball::awaySchool.getPrimaryColor();
    homeTeam = team;

    int red, green, blue;
    if (homeTeam) {
        red = -1*homeColor.red() *GRADIENT_LEVEL + homeColor.red();
        green = -1*homeColor.green() *GRADIENT_LEVEL + homeColor.green();
        blue = -1*homeColor.blue() *GRADIENT_LEVEL + homeColor.blue();

        QColor end(red, green, blue);
        if (end == QColor(0,0,0))
            end = QColor(1,1,1);
        mainGradient.setColorAt(0, homeColor);
        mainGradient.setColorAt(1, end);
    }
    else {

        red = -1*awayColor.red() *GRADIENT_LEVEL + awayColor.red();
        green = -1*awayColor.green() *GRADIENT_LEVEL + awayColor.green();
        blue = -1*awayColor.blue() *GRADIENT_LEVEL + awayColor.blue();
        QColor end2(red, green, blue);
        if (end2 == QColor(0,0,0))
            end2 = QColor(1,1,1);
        //awayGradient.setColorAt(.4, awayColor);
        mainGradient.setColorAt(0, awayColor);
        mainGradient.setColorAt(1, end2);
    }
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
    QColor homeColor = MiamiAllAccessBaseball::homeSchool.getPrimaryColor();
    QColor awayColor = MiamiAllAccessBaseball::awaySchool.getPrimaryColor();
    int red, green, blue;
    red = -1*homeColor.red() *GRADIENT_LEVEL + homeColor.red();
    green = -1*homeColor.green() *GRADIENT_LEVEL + homeColor.green();
    blue = -1*homeColor.blue() *GRADIENT_LEVEL + homeColor.blue();

    QColor end(red, green, blue);
    if (end == QColor(0,0,0))
        end = QColor(1,1,1);
    //homeGradient.setColorAt(.4, homeColor);
    homeGradient.setColorAt(0, homeColor);
    homeGradient.setColorAt(1, end);
    //homeGradient.setColorAt(0, end);

    red = -1*awayColor.red() *GRADIENT_LEVEL + awayColor.red();
    green = -1*awayColor.green() *GRADIENT_LEVEL + awayColor.green();
    blue = -1*awayColor.blue() *GRADIENT_LEVEL + awayColor.blue();
    QColor end2(red, green, blue);
    if (end2 == QColor(0,0,0))
        end2 = QColor(1,1,1);
    //awayGradient.setColorAt(.4, awayColor);
    awayGradient.setColorAt(0, awayColor);
    awayGradient.setColorAt(1, end2);
   // awayGradient.setColorAt(0, end2);

//    mainGradient.setColorAt(0, QColor(25,25,25));
//    mainGradient.setColorAt(.5, QColor(83,83,83));
//    mainGradient.setColorAt(1, QColor(25,25,25));
}


