#include "CommercialGraphic.h"
#include <QFontMetrics>
#include <QGraphicsScene>

//#define WIDTH 1920/2
//#define NAME_WIDTH 860
#define RECT_HEIGHT 120
#define CENTER_OFFSET 100
#define BLACK_BAR_HEIGHT 60
#define GRADIENT_LEVEL .5
#define SHOW_CLOCK 0
#define INTERMISSION 1
#define FINAL 2

CommercialGraphic::CommercialGraphic(BaseballGame* game, int width, QString pawayLogo, QGraphicsItem* parent) :
    QGraphicsPixmapItem(parent), blackBar(QPixmap(":/images/ppBar.png")),
    blockText(QPixmap(":/images/M.png")) {
    baseballGame = game;
    show = false;
    WIDTH = width;
    NAME_WIDTH = WIDTH/4;
    inGame  = false;
    QFont font("Arial", 60, QFont::Bold);
    QFont sponsorFont("Arial", 36, QFont::Bold);
#ifdef Q_OS_OSX
    font.setPointSize(68);
    sponsorFont.setPointSize(44);
#endif
    //QPixmap pix(pawayLogo);
    away = new QGraphicsTextItem(game->getAwayName());
    away->setFont(font);
    checkAwayFont();
    home = new QGraphicsTextItem(game->getHomeName());
    home->setFont(font);

    descriptiveFont = sponsorFont;
    prepareGradients(game->getAwayColor(), game->getHomeColor());
    maaText = "Miami All-Access";
    clockStatus = SHOW_CLOCK;

    awayLogo = new QPixmap(pawayLogo);
    if (awayLogo->height() > 120) {
        *awayLogo = awayLogo->scaledToHeight(120, Qt::SmoothTransformation);
    }
    if (blockText.height() > 120) {
        blockText = blockText.scaledToHeight(120, Qt::SmoothTransformation);
    }
    /*  if (awayLogo->width() > 1919) {
       *awayLogo =  awayLogo->scaledToWidth(800, Qt::SmoothTransformation);
    }*/
}

void CommercialGraphic::paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
                              QWidget* widget) {
    if (show){
        painter->setPen(QColor(255, 255, 255));
        painter->drawPixmap(WIDTH/4, -BLACK_BAR_HEIGHT, WIDTH * .75, BLACK_BAR_HEIGHT, blackBar);

        painter->setFont(descriptiveFont);
        painter->drawText(WIDTH / 4, -BLACK_BAR_HEIGHT, WIDTH/4, BLACK_BAR_HEIGHT, Qt::AlignCenter, maaText);
        painter->drawText(WIDTH*.75, -BLACK_BAR_HEIGHT, CENTER_OFFSET-10, BLACK_BAR_HEIGHT, Qt::AlignVCenter | Qt::AlignRight, "R");
        painter->drawText(WIDTH*.75+ CENTER_OFFSET, -BLACK_BAR_HEIGHT, CENTER_OFFSET-10, BLACK_BAR_HEIGHT, Qt::AlignVCenter | Qt::AlignRight, "H");
        painter->drawText(WIDTH*.75 + CENTER_OFFSET +CENTER_OFFSET, -BLACK_BAR_HEIGHT, CENTER_OFFSET-10, BLACK_BAR_HEIGHT, Qt::AlignVCenter | Qt::AlignRight, "E");

        painter->fillRect(0, 0, WIDTH, RECT_HEIGHT, awayTeamGradient);
        painter->fillRect(0, RECT_HEIGHT, WIDTH, RECT_HEIGHT, homeTeamGradient);
        painter->setFont(away->font());
        painter->drawText(WIDTH/4, 0, NAME_WIDTH*2, RECT_HEIGHT, Qt::AlignCenter, away->toPlainText());
        //painter->drawPixmap(WIDTH - CENTER_OFFSET - 100 - awayLogo.width(), 20, awayLogo);
        painter->setOpacity(.996);
        painter->drawPixmap(WIDTH /4, 0, *awayLogo);
        painter->setFont(home->font());
        painter->drawText(WIDTH/4, RECT_HEIGHT, NAME_WIDTH*2, RECT_HEIGHT, Qt::AlignCenter, home->toPlainText());
        painter->drawPixmap(WIDTH/4, RECT_HEIGHT, blockText);
        painter->setOpacity(1);

        painter->fillRect(WIDTH*.75, 0, CENTER_OFFSET, RECT_HEIGHT*2, QColor(1,1,1, 100));


        painter->drawText(WIDTH*.75, 0, CENTER_OFFSET-10, RECT_HEIGHT, Qt::AlignVCenter | Qt::AlignRight, awayScore);
        painter->drawText(WIDTH*.75, RECT_HEIGHT, CENTER_OFFSET-10, RECT_HEIGHT, Qt::AlignVCenter | Qt::AlignRight, homeScore);

        painter->drawText(WIDTH*.75+ CENTER_OFFSET, 0, CENTER_OFFSET-10, RECT_HEIGHT, Qt::AlignVCenter | Qt::AlignRight, hitsAway);
        painter->drawText(WIDTH*.75 +CENTER_OFFSET, RECT_HEIGHT, CENTER_OFFSET-10, RECT_HEIGHT, Qt::AlignVCenter | Qt::AlignRight, hitsHome);

        painter->drawText(WIDTH*.75 + CENTER_OFFSET +CENTER_OFFSET, 0, CENTER_OFFSET-10, RECT_HEIGHT, Qt::AlignVCenter | Qt::AlignRight, errorsAway);
        painter->drawText(WIDTH*.75 + CENTER_OFFSET + CENTER_OFFSET, RECT_HEIGHT, CENTER_OFFSET-10, RECT_HEIGHT, Qt::AlignVCenter | Qt::AlignRight, errorsHome);


        painter->drawPixmap(WIDTH/2 - 200, RECT_HEIGHT*2, WIDTH/2 - (WIDTH/2- 400), BLACK_BAR_HEIGHT, blackBar);
        painter->setFont(descriptiveFont);
        if (clockStatus == FINAL) {
            painter->drawText(WIDTH/2 - 200, RECT_HEIGHT*2, WIDTH/2 - (WIDTH/2- 400), BLACK_BAR_HEIGHT, Qt::AlignCenter, "FINAL");
        }
        else {
            painter->drawText(WIDTH/2 - 200, RECT_HEIGHT*2, WIDTH/2 - (WIDTH/2- 400), BLACK_BAR_HEIGHT, Qt::AlignCenter, clock);
        }
    }
}

void CommercialGraphic::prepareAndShow()
{
    awayScore = QString::number(baseballGame->getAwayScore());
    homeScore = QString::number(baseballGame->getHomeScore());
    hitsHome = QString::number(baseballGame->getHomeHits());
    hitsAway = QString::number(baseballGame->getAwayHits());
    errorsAway = QString::number(baseballGame->getAwayErrors());
    errorsHome = QString::number(baseballGame->getHomeErrors());
    clock = clockStatus == SHOW_CLOCK? baseballGame->getInningText() : "FINAL";
    show = true;
    //updateClock();
    scene()->update(0,y() - BLACK_BAR_HEIGHT,1920,1080);
}

void CommercialGraphic::updateClock()
{
    if (show) {
        if (clockStatus == SHOW_CLOCK) {
            //clock = baseballGame->getGameClock()->toString();
            //scene()->update(x() + WIDTH/2 - 200, y() + RECT_HEIGHT*2, WIDTH/2 - (WIDTH/2- 400), BLACK_BAR_HEIGHT);
        }
        else if (clockStatus == INTERMISSION) {
            clock = "INT";
        }
        else {
            clock = "FINAL";
        }


    }
}

void CommercialGraphic::showClock() {
    clockStatus = SHOW_CLOCK;
    updateClock();
    if (show)
        scene()->update(x() + WIDTH/2 - 200, y() + RECT_HEIGHT*2, WIDTH/2 - (WIDTH/2- 400), BLACK_BAR_HEIGHT);
}

void CommercialGraphic::intermissionTime()
{
    clockStatus = INTERMISSION;
    updateClock();
    if (show)
        scene()->update(x() + WIDTH - 200, y() + RECT_HEIGHT, WIDTH - (WIDTH- 400), BLACK_BAR_HEIGHT);
}

void CommercialGraphic::finalTime()
{
    clockStatus = FINAL;
    updateClock();
    if (show)
        scene()->update(x() + WIDTH/2 - 200, y() + RECT_HEIGHT*2, WIDTH/2 - (WIDTH/2- 400), BLACK_BAR_HEIGHT);
}

void CommercialGraphic::hide()
{
    if (show) {
        show = false;
        scene()->update(0,y() - BLACK_BAR_HEIGHT,1920,1080);
    }
}

void CommercialGraphic::checkAwayFont()
{
    int fontPointSize = away->font().pointSize();
    int subtraction = 1;
    QFontMetrics fontSize(away->font());
    while (fontSize.width(away->toPlainText()) > NAME_WIDTH) {
        QFont tempFont("Arial", fontPointSize - subtraction, QFont::Bold);
        subtraction++;
        away->setFont(tempFont);
        QFontMetrics temp(away->font());
        fontSize = temp;
    }
}

void CommercialGraphic::prepareGradients(QColor awayColor, QColor homeColor)
{
    homeTeamGradient.setStart(0, RECT_HEIGHT);
    homeTeamGradient.setFinalStop(0, RECT_HEIGHT*2);
    awayTeamGradient.setStart(0,0);
    awayTeamGradient.setFinalStop(0, 120);
    int red, green, blue;
    red = -1*homeColor.red() *GRADIENT_LEVEL + homeColor.red();
    green = -1*homeColor.green() *GRADIENT_LEVEL + homeColor.green();
    blue = -1*homeColor.blue() *GRADIENT_LEVEL + homeColor.blue();

    QColor end(red, green, blue);
    if (end == QColor(0,0,0))
        end = QColor(1,1,1);
    homeTeamGradient.setColorAt(.4, homeColor);
    homeTeamGradient.setColorAt(.6, homeColor);
    homeTeamGradient.setColorAt(1, end);
    homeTeamGradient.setColorAt(0, end);

    red = -1*awayColor.red() *GRADIENT_LEVEL + awayColor.red();
    green = -1*awayColor.green() *GRADIENT_LEVEL + awayColor.green();
    blue = -1*awayColor.blue() *GRADIENT_LEVEL + awayColor.blue();
    QColor end2(red, green, blue);
    if (end2 == QColor(0,0,0))
        end2 = QColor(1,1,1);
    awayTeamGradient.setColorAt(.4, awayColor);
    awayTeamGradient.setColorAt(.6, awayColor);
    awayTeamGradient.setColorAt(1, end2);
    awayTeamGradient.setColorAt(0, end2);
}
