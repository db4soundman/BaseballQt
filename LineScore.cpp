#include "LineScore.h"
#include <QFontMetrics>
#include <QGraphicsScene>
#include <algorithm>
#include "MiamiAllAccessBaseball.h"
#define WIDTH 620
#define HEIGHT 160
#define TEAM_HEIGHT 50
#define NAME_WIDTH 860
#define LOGO_WIDTH 70
#define V_TEAM_Y 30
#define H_TEAM_Y (V_TEAM_Y + TEAM_HEIGHT)
#define RUNS_X 490
#define HITS_X (RUNS_X + 40)
#define ERRORS_X (HITS_X + 40)
#define GRADIENT_LEVEL .5
#define SHOW_CLOCK 0
#define INTERMISSION 1
#define FINAL 2

LineScore::LineScore(BaseballGame *pGame, QObject *parent) :
    homeLogo(MiamiAllAccessBaseball::homeSchool.getLogo()) {
        baseballGame = pGame;
        show = false;
        inGame  = false;
        QFont font("Arial", 20, QFont::Bold);
        away = new QGraphicsTextItem(MiamiAllAccessBaseball::awaySchool.getTitle());
        away->setFont(font);
        getDueUpFont();
        home = new QGraphicsTextItem(MiamiAllAccessBaseball::homeSchool.getTitle());
        home->setFont(font);
        networkLogo = QPixmap(":/images/Watermark.png").scaledToWidth(200, Qt::SmoothTransformation);
        homeTeamGradient.setStart(0, H_TEAM_Y);
        homeTeamGradient.setFinalStop(0, H_TEAM_Y + TEAM_HEIGHT);
        awayTeamGradient.setStart(0,V_TEAM_Y);
        awayTeamGradient.setFinalStop(0, V_TEAM_Y + TEAM_HEIGHT);
        blackGradient.setStart(0,0);
        blackGradient.setFinalStop(0, V_TEAM_Y);
        //descriptiveFont = sponsorFont;
        prepareGradients(MiamiAllAccessBaseball::awaySchool.getPrimaryColor(), MiamiAllAccessBaseball::homeSchool.getPrimaryColor());

        clockStatus = SHOW_CLOCK;

        awayLogo = MiamiAllAccessBaseball::awaySchool.getLogo();
        if (awayLogo.height() > TEAM_HEIGHT) {
            awayLogo = awayLogo.scaledToHeight(TEAM_HEIGHT, Qt::SmoothTransformation);
        }
        if (homeLogo.height() > TEAM_HEIGHT) {
            homeLogo = homeLogo.scaledToHeight(TEAM_HEIGHT, Qt::SmoothTransformation);
        }
        if (awayLogo.width() > LOGO_WIDTH) {
           awayLogo =  awayLogo.scaledToWidth(LOGO_WIDTH, Qt::SmoothTransformation);
        }
        if (homeLogo.width() > LOGO_WIDTH) {
           homeLogo =  homeLogo.scaledToWidth(LOGO_WIDTH, Qt::SmoothTransformation);
        }

        awayHeightOffset = (TEAM_HEIGHT - awayLogo.height()) / 2;
        awayWidthOffset = (LOGO_WIDTH - awayLogo.width()) / 2;

        homeHeightOffset = (TEAM_HEIGHT - homeLogo.height()) / 2;
        homeWidthOffset = (LOGO_WIDTH - homeLogo.width()) / 2;

}

void LineScore::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (show){
        QList<int>awayLineScore = baseballGame->getAwayLineScore();
        QList<int>homeLineScore = baseballGame->getHomeLineScore();
        painter->setPen(QColor(255, 255, 255));
        painter->fillRect(0, 0, WIDTH, V_TEAM_Y, blackGradient);
       // painter->drawPixmap(0,(V_TEAM_Y - networkLogo.height()) / 2, networkLogo);

        painter->fillRect(0, V_TEAM_Y, WIDTH, TEAM_HEIGHT, awayTeamGradient);
        painter->fillRect(0, H_TEAM_Y, WIDTH, TEAM_HEIGHT, homeTeamGradient);
        painter->setFont(away->font());
        painter->fillRect(0, V_TEAM_Y, LOGO_WIDTH, TEAM_HEIGHT, MiamiAllAccessBaseball::awaySchool.getPrimaryLogoBg());
        painter->drawPixmap(awayWidthOffset, V_TEAM_Y + awayHeightOffset, awayLogo);
        painter->setFont(home->font());
        painter->fillRect(0, H_TEAM_Y, LOGO_WIDTH, TEAM_HEIGHT, MiamiAllAccessBaseball::homeSchool.getPrimaryLogoBg());
        painter->drawPixmap(homeWidthOffset, H_TEAM_Y + homeHeightOffset, homeLogo);

        painter->setFont(QFont("Arial", 16, QFont::Bold));

        for (int i = 0; i < 3; i++){
            for (int j = 1; j < 4; j++) {
                painter->drawText(50 + (40*(3*i+j)), 0, 40, V_TEAM_Y, Qt::AlignVCenter | Qt::AlignRight, QString::number(i*3+j));
            }
        }

        for(int i = 0; i < std::min(awayLineScore.length(), 9); i++) {
            painter->drawText(50 + (40*(i+1)), V_TEAM_Y,40,TEAM_HEIGHT, Qt::AlignVCenter | Qt::AlignRight, QString::number(awayLineScore[i]));
        }
        for(int i = 0; i < std::min(homeLineScore.length(), 9); i++) {
            painter->drawText(50 + (40*(i+1)), H_TEAM_Y,40,TEAM_HEIGHT, Qt::AlignVCenter | Qt::AlignRight, QString::number(homeLineScore[i]));
        }

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
        painter->setFont(getDueUpFont());
        painter->drawText(0,  H_TEAM_Y + TEAM_HEIGHT, WIDTH, HEIGHT - (H_TEAM_Y + TEAM_HEIGHT), Qt::AlignCenter, clock);

    }

}

void LineScore::prepareAndShow()
{
    awayScore = QString::number(baseballGame->getAwayScore());
    homeScore = QString::number(baseballGame->getHomeScore());
    hitsHome = QString::number(baseballGame->getHomeHits());
    hitsAway = QString::number(baseballGame->getAwayHits());
    errorsAway = QString::number(baseballGame->getAwayErrors());
    errorsHome = QString::number(baseballGame->getHomeErrors());
    dueUp = baseballGame->getDueUp();
//    prepareDueUp();
    clock = clockStatus == SHOW_CLOCK? baseballGame->getInningText() : clock;
    clock = clock.replace("Top", "START").replace("Bot", "MID");
    show = true;
    updateClock();
    emit addNoTransparencyZone(QRect(x(), V_TEAM_Y + y(), LOGO_WIDTH, TEAM_HEIGHT));
    scene()->update(x(),y(),WIDTH, HEIGHT);
}

void LineScore::updateClock()
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

void LineScore::showClock()
{
    clockStatus = SHOW_CLOCK;
    updateClock();
    if (show)
        prepareAndShow();
}

void LineScore::intermissionTime()
{
    clockStatus = INTERMISSION;
    updateClock();
    if (show)
        prepareAndShow();
}

void LineScore::finalTime()
{
    clockStatus = FINAL;
    updateClock();
    if (show)
        prepareAndShow();
}

void LineScore::hideGraphic()
{
    if (show) {
        show = false;
        emit removeNoTransparencyZone(QRect(x(), V_TEAM_Y + y(), LOGO_WIDTH, TEAM_HEIGHT));
        scene()->update(x(), y(), WIDTH, HEIGHT);
    }
}

QFont LineScore::getDueUpFont()
{
    int pointSize = 16;
    int subtraction = 0;
    QFont font("Arial", pointSize, QFont::Bold);
    QFontMetrics fontSize(font);
    while (fontSize.width(dueUpString) > WIDTH - 10) {
        QFont tempFont("Arial", pointSize - subtraction, QFont::Bold);
        subtraction++;
        QFontMetrics temp(tempFont);
        fontSize = temp;
    }
    return QFont("Arial", pointSize - subtraction, QFont::Bold);
}

void LineScore::prepareGradients(QColor awayColor, QColor homeColor)
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

void LineScore::prepareDueUp()
{
    dueUpString = "DUE UP: " + dueUp[0].split(" ").last() +", " + dueUp[1].split(" ").last() + ", " + dueUp[2].split(" ").last();
}
