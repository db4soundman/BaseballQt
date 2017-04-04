#include "CommercialGraphic.h"
#include <QFontMetrics>
#include <QGraphicsScene>

#define WIDTH 320
#define HEIGHT 160
#define TEAM_HEIGHT 50
#define NAME_WIDTH 860
#define LOGO_WIDTH 70
#define V_TEAM_Y 30
#define H_TEAM_Y (V_TEAM_Y + TEAM_HEIGHT)
#define RUNS_X 190
#define HITS_X (RUNS_X + 40)
#define ERRORS_X (HITS_X + 40)
#define GRADIENT_LEVEL .5
#define SHOW_CLOCK 0
#define INTERMISSION 1
#define FINAL 2

CommercialGraphic::CommercialGraphic(BaseballGame* game, int width, QPixmap pawayLogo, QGraphicsItem* parent) :
    QGraphicsRectItem(parent), homeLogo(QPixmap(":/images/M.png")) {
    baseballGame = game;
    show = false;
    inGame  = false;
    QFont font("Arial", 20, QFont::Bold);
    away = new QGraphicsTextItem(game->getAwayName());
    away->setFont(font);
    checkAwayFont();
    home = new QGraphicsTextItem(game->getHomeName());
    home->setFont(font);
    networkLogo = QPixmap(":/images/Watermark.png").scaledToWidth(200, Qt::SmoothTransformation);
    homeTeamGradient.setStart(0, H_TEAM_Y);
    homeTeamGradient.setFinalStop(0, H_TEAM_Y + TEAM_HEIGHT);
    awayTeamGradient.setStart(0,V_TEAM_Y);
    awayTeamGradient.setFinalStop(0, V_TEAM_Y + TEAM_HEIGHT);
    blackGradient.setStart(0,0);
    blackGradient.setFinalStop(0, V_TEAM_Y);
    //descriptiveFont = sponsorFont;
    prepareGradients(game->getAwayColor(), game->getHomeColor());
    maaText = "Miami Baseball";
    clockStatus = SHOW_CLOCK;

    awayLogo = new QPixmap(pawayLogo);
    if (awayLogo->height() > TEAM_HEIGHT) {
        *awayLogo = awayLogo->scaledToHeight(TEAM_HEIGHT, Qt::SmoothTransformation);
    }
    if (homeLogo.height() > TEAM_HEIGHT) {
        homeLogo = homeLogo.scaledToHeight(TEAM_HEIGHT, Qt::SmoothTransformation);
    }
    if (awayLogo->width() > LOGO_WIDTH) {
       *awayLogo =  awayLogo->scaledToWidth(LOGO_WIDTH, Qt::SmoothTransformation);
    }

    awayHeightOffset = (TEAM_HEIGHT - awayLogo->height()) / 2;
    awayWidthOffset = (LOGO_WIDTH - awayLogo->width()) / 2;
}

void CommercialGraphic::paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
                              QWidget* widget) {
    if (show){
        painter->setPen(QColor(255, 255, 255));
        painter->fillRect(0, 0, WIDTH, V_TEAM_Y, blackGradient);
        painter->drawPixmap(0,(V_TEAM_Y - networkLogo.height()) / 2, networkLogo);

//        painter->drawText(WIDTH / 4, -BLACK_BAR_HEIGHT, WIDTH/4, BLACK_BAR_HEIGHT, Qt::AlignCenter, maaText);


        painter->fillRect(0, V_TEAM_Y, WIDTH, TEAM_HEIGHT, awayTeamGradient);
        painter->fillRect(0, H_TEAM_Y, WIDTH, TEAM_HEIGHT, homeTeamGradient);
        painter->setFont(away->font());
        //painter->drawText(WIDTH/4, 0, NAME_WIDTH*2, TEAM_HEIGHT, Qt::AlignCenter, away->toPlainText());
        //painter->drawPixmap(WIDTH - CENTER_OFFSET - 100 - awayLogo.width(), 20, awayLogo);

        painter->drawPixmap(awayWidthOffset, V_TEAM_Y + awayHeightOffset, *awayLogo);
        painter->setFont(home->font());
        //painter->drawText(WIDTH/4, TEAM_HEIGHT, NAME_WIDTH*2, TEAM_HEIGHT, Qt::AlignCenter, home->toPlainText());
        painter->drawPixmap(0, H_TEAM_Y, homeLogo);

        //painter->fillRect(WIDTH*.75 - CENTER_OFFSET, 0, CENTER_OFFSET, TEAM_HEIGHT*2, QColor(1,1,1, 100));

        painter->setFont(QFont("Arial", 16, QFont::Bold));
        painter->drawText(RUNS_X, 0, 40, V_TEAM_Y, Qt::AlignVCenter | Qt::AlignRight, "R");
        painter->drawText(HITS_X, 0, 40, V_TEAM_Y, Qt::AlignVCenter | Qt::AlignRight, "H");
        painter->drawText(ERRORS_X, 0, 40, V_TEAM_Y, Qt::AlignVCenter | Qt::AlignRight, "E");

        painter->setFont(home->font());
        painter->drawText(RUNS_X, V_TEAM_Y, 40, TEAM_HEIGHT, Qt::AlignVCenter | Qt::AlignRight, awayScore);
        painter->drawText(RUNS_X, H_TEAM_Y, 40, TEAM_HEIGHT, Qt::AlignVCenter | Qt::AlignRight, homeScore);
        painter->drawText(HITS_X, V_TEAM_Y, 40, TEAM_HEIGHT, Qt::AlignVCenter | Qt::AlignRight, hitsAway);
        painter->drawText(HITS_X, H_TEAM_Y, 40, TEAM_HEIGHT, Qt::AlignVCenter | Qt::AlignRight, hitsHome);

        painter->drawText(ERRORS_X, V_TEAM_Y, 40, TEAM_HEIGHT, Qt::AlignVCenter | Qt::AlignRight, errorsAway);
        painter->drawText(ERRORS_X, H_TEAM_Y, 40, TEAM_HEIGHT, Qt::AlignVCenter | Qt::AlignRight, errorsHome);


        painter->fillRect(0, H_TEAM_Y + TEAM_HEIGHT, WIDTH, HEIGHT - (H_TEAM_Y + TEAM_HEIGHT), QColor(50,50,50));
        painter->setFont(QFont("Arial", 16, QFont::Bold));
        painter->drawText(0,  H_TEAM_Y + TEAM_HEIGHT, WIDTH, HEIGHT - (H_TEAM_Y + TEAM_HEIGHT), Qt::AlignCenter, clock);

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
    clock = clockStatus == SHOW_CLOCK? baseballGame->getInningText() : clock;
    clock = clock.replace("Top", "START").replace("Bot", "MID");
    show = true;
    updateClock();
    emit addNoTransparencyZone(QRect(x(), V_TEAM_Y + y(), LOGO_WIDTH, TEAM_HEIGHT));
    scene()->update(x(),y(),WIDTH, HEIGHT);
}

void CommercialGraphic::updateClock()
{
    if (show) {
        if (clockStatus == SHOW_CLOCK) {
            //clock = baseballGame->getGameClock()->toString();
            //scene()->update(x() + WIDTH/2 - 200, y() + TEAM_HEIGHT*2, WIDTH/2 - (WIDTH/2- 400), BLACK_BAR_HEIGHT);
        }
        else if (clockStatus == INTERMISSION) {
            clock = "DELAYED";
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
        prepareAndShow();
}

void CommercialGraphic::intermissionTime()
{
    clockStatus = INTERMISSION;
    updateClock();
    if (show)
        prepareAndShow();
}

void CommercialGraphic::finalTime()
{
    clockStatus = FINAL;
    updateClock();
    if (show)
        prepareAndShow();
}

void CommercialGraphic::hide()
{
    if (show) {
        show = false;
        emit removeNoTransparencyZone(QRect(x(), V_TEAM_Y + y(), LOGO_WIDTH, TEAM_HEIGHT));
        scene()->update(x(), y(), WIDTH, HEIGHT);
    }
}
QString CommercialGraphic::getMaaText() const
{
    return maaText;
}

void CommercialGraphic::setMaaText(const QString &value)
{
    maaText = value;
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

    int red, green, blue;
    red = -1*homeColor.red() *GRADIENT_LEVEL + homeColor.red();
    green = -1*homeColor.green() *GRADIENT_LEVEL + homeColor.green();
    blue = -1*homeColor.blue() *GRADIENT_LEVEL + homeColor.blue();

    QColor end(red, green, blue);
    if (end == QColor(0,0,0))
        end = QColor(1,1,1);
    homeTeamGradient.setColorAt(0, homeColor);
    homeTeamGradient.setColorAt(1, end);

    red = -1*awayColor.red() *GRADIENT_LEVEL + awayColor.red();
    green = -1*awayColor.green() *GRADIENT_LEVEL + awayColor.green();
    blue = -1*awayColor.blue() *GRADIENT_LEVEL + awayColor.blue();
    QColor end2(red, green, blue);
    if (end2 == QColor(0,0,0))
        end2 = QColor(1,1,1);
    awayTeamGradient.setColorAt(0, awayColor);
    awayTeamGradient.setColorAt(1, end2);

    blackGradient.setColorAt(0, QColor(50,50,50));
    blackGradient.setColorAt(1, QColor(25,25,25));

}
