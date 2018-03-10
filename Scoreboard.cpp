#include "Scoreboard.h"
#include <QGraphicsScene>
#include <QMessageBox>
#include <QFontMetrics>
#include <QFontInfo>

#define GRADIENT_LEVEL .3
#define AWAY_PP 1
#define HOME_PP 2
#define NEUTRAL 3
#define TEAM_NAME_WIDTH 310
#define RANK_WIDTH 50
#define TEAM_BOX_Y 6
#define SCORE_WIDTH 78
#define SCOREBOARD_WIDTH 480
#define SCOREBOARD_HEIGHT 126
//100
#define TEAM_BOX_HEIGHT 48
#define TEAM_BOX_WIDTH (TEAM_NAME_WIDTH + SCORE_WIDTH)
#define V_TEAM_BOX_STARTX 0
#define V_TEAM_BOX_STARTY 0
#define H_TEAM_BOX_STARTX 0
#define H_TEAM_BOX_STARTY TEAM_BOX_HEIGHT
//(SCOREBOARD_HEIGHT/3)
#define LOGO_WIDTH 50
#define CLOCK_FIELD_X 0
#define CLOCK_FIELD_Y (SCOREBOARD_HEIGHT/3 * 2)
#define CLOCK_FIELD_WIDTH ((600 - TEAM_BOX_WIDTH)/2)
#define CLOCK_FIELD_HEIGHT 30
#define INNING_X 0
//TEAM_BOX_WIDTH
#define INNING_Y (SCOREBOARD_HEIGHT-30)
//0
#define COUNT_X INNING_X+80
//(TEAM_BOX_WIDTH + CLOCK_FIELD_WIDTH)
#define COUNT_Y INNING_Y
//0
#define OUTS_X (COUNT_X + 80)
//COUNT_X
#define OUTS_Y INNING_Y
//(SCOREBOARD_HEIGHT - 45)
#define DIAMOND_START 390
#define PP_BAR_HEIGHT 38
#define SPONSOR_BAR_Y 50
#define SPONSOR_BAR_HEIGHT 35

Scoreboard::Scoreboard(QColor awayCol, QColor homeCol, QString awayTeam, QString homeTeam,
                       QString sponsorText, /*Clock* clock,*/ QString pAwayRank, QString pHomeRank, QPixmap pawayLogo) :
    homeColor(homeCol), awayColor(awayCol) {
    QFont font("Arial", 24, QFont::Bold);
    QFont sponsorFont("Arial", 18, QFont::Bold);
#ifdef Q_OS_OSX
    font.setPointSize(40);
    sponsorFont.setPointSize(28);
    #endif
    watermark = QPixmap(":/images/Watermark.png");
    watermark = watermark.scaledToWidth(200, Qt::SmoothTransformation);
    defaultSponsorText = sponsorFont;
    show =firstBase = secondBase = thirdBase = false;
    setRect(0,0,SCOREBOARD_WIDTH,SCOREBOARD_HEIGHT);

    homeLogo = new QPixmap(":/images/M.png");
    awayLogo = new QPixmap(pawayLogo);
    inning = "1";
    topOfInning = true;

    *homeLogo = homeLogo->scaledToHeight(TEAM_BOX_HEIGHT, Qt::SmoothTransformation);
    if (homeLogo->width() > LOGO_WIDTH)
        *homeLogo = homeLogo->scaledToWidth(LOGO_WIDTH, Qt::SmoothTransformation);
    homeLogoOffset = (TEAM_BOX_HEIGHT - homeLogo->height()) / 2;

    *awayLogo = awayLogo->scaledToHeight(TEAM_BOX_HEIGHT, Qt::SmoothTransformation);
    if (awayLogo->width() > LOGO_WIDTH)
        *awayLogo = awayLogo->scaledToWidth(LOGO_WIDTH, Qt::SmoothTransformation);
    awayLogoHeightOffset = (TEAM_BOX_HEIGHT - awayLogo->height()) / 2;
    awayLogoWidthOffset = (LOGO_WIDTH - awayLogo->width()) / 2;

    awayName = new QGraphicsTextItem(awayTeam);
    homeName = new QGraphicsTextItem(homeTeam);
    awayName->setFont(font);
    homeName->setFont(font);
    awayScore = new QGraphicsTextItem("0");
    awayScore->setFont(font);
    homeScore = new QGraphicsTextItem("0");
    homeScore->setFont(font);
    topBarText = new QGraphicsTextItem(sponsorText);
    this->sponsorText = sponsorText;
    topBarText->setFont(defaultSponsorText);

    homeGradient.setStart(0, H_TEAM_BOX_STARTY);
    awayGradient.setStart(0, V_TEAM_BOX_STARTY);
    homeGradient.setFinalStop(0,H_TEAM_BOX_STARTY + TEAM_BOX_HEIGHT);
    awayGradient.setFinalStop(0,V_TEAM_BOX_STARTY + TEAM_BOX_HEIGHT);
    mainGradient.setStart(0,0);
    mainGradient.setFinalStop(0, SCOREBOARD_HEIGHT);
    clockGradient.setStart(0,INNING_Y);
    clockGradient.setFinalStop(0, SCOREBOARD_HEIGHT);
    ppGradient.setStart(0, SCOREBOARD_HEIGHT);
    ppGradient.setFinalStop(0, 92);
    scoreGradient.setStart(0, TEAM_BOX_Y);
    scoreGradient.setFinalStop(0, TEAM_BOX_Y + 44);
    prepareColor();
    // penalty gradient
//    penaltyGradient.setStart(0, SCOREBOARD_HEIGHT);
//    penaltyGradient.setFinalStop(0, SCOREBOARD_HEIGHT + PP_BAR_HEIGHT);
//    penaltyGradient.setColorAt(0, QColor(255, 255, 0));
//    penaltyGradient.setColorAt(1, QColor(188, 188, 0));

    QFont rankFont("Arial", 20, QFont::Bold);
    awayRank = new QGraphicsTextItem(pAwayRank);
    homeRank = new QGraphicsTextItem(pHomeRank);
    awayRank->setFont(rankFont);
    homeRank->setFont(rankFont);
    awayRankOffset = homeRankOffset = LOGO_WIDTH;
    if (!awayRank->toPlainText().isEmpty()) {
        awayRankOffset += RANK_WIDTH;
    }

    if (!homeRank->toPlainText().isEmpty()) {
        homeRankOffset += RANK_WIDTH;
    }

    pitchingChange = false;
    showPP = false;
    sponsor = false;
    showPdAndClock = true;
    showClock = true;
    count = "0-0";
    out = 0;
    this->clock = clock;
    //connect(clock, SIGNAL(clockUpdated()), this, SLOT(updateClock()));
    prepareAwayName();

}

void
Scoreboard::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                  QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if (show) {
//        if (!useTransparency)
//            painter->drawPixmap(0,-49,SCOREBOARD_WIDTH,49, *topBar);
        //painter->drawPixmap(0, 0, this->pixmap());
        painter->fillRect(0,0,SCOREBOARD_WIDTH, SCOREBOARD_HEIGHT, mainGradient);
        //painter->drawPixmap(34, 4, 66, 50, *homeLogo);
        //Clock - Game time...draw clock first since default color is black
        painter->setFont(QFont("Arial",18, QFont::Bold));
        painter->setPen(QColor(255,255,255));
        painter->fillRect(INNING_X, INNING_Y, SCOREBOARD_WIDTH,CLOCK_FIELD_HEIGHT, clockGradient);
        painter->drawPixmap(OUTS_X + CLOCK_FIELD_WIDTH, OUTS_Y + 5, watermark);
        if (showPdAndClock) {
            painter->drawText(INNING_X, INNING_Y, CLOCK_FIELD_WIDTH,CLOCK_FIELD_HEIGHT, Qt::AlignHCenter, (topOfInning ? "TOP " : "BOT ") + inning);
            //painter->setPen(QColor(255,255,255));
            //painter->drawText(CLOCK_FIELD_X + CLOCK_FIELD_WIDTH/4, CLOCK_FIELD_Y, CLOCK_FIELD_WIDTH/4, CLOCK_FIELD_HEIGHT, Qt::AlignCenter, inning);
            //painter->setPen(QColor(1,1,1));
            painter->drawText(COUNT_X, COUNT_Y, CLOCK_FIELD_WIDTH, CLOCK_FIELD_HEIGHT, Qt::AlignHCenter,
                              count);
            painter->drawText(OUTS_X, OUTS_Y, CLOCK_FIELD_WIDTH, CLOCK_FIELD_HEIGHT, Qt::AlignHCenter,
                              QString::number(out) + " OUT");
            //painter->fillRect(CLOCK_FIELD_X, topOfInning ? 3 : 48-5, CLOCK_FIELD_WIDTH/3, 5, QColor(1,1,1));

        }
        else {
            painter->drawText(INNING_X, INNING_Y, SCOREBOARD_WIDTH / 2, CLOCK_FIELD_HEIGHT, Qt::AlignHCenter, centeredTimeText);
        }
        painter->setFont(homeName->font());
        // Away text
        painter->fillRect(V_TEAM_BOX_STARTX, V_TEAM_BOX_STARTY, TEAM_BOX_WIDTH, TEAM_BOX_HEIGHT, awayGradient );
        painter->setPen(QColor(255,255,255));
        //painter->drawRect(V_TEAM_BOX_STARTX , V_TEAM_BOX_STARTY, TEAM_BOX_WIDTH, TEAM_BOX_HEIGHT);
        // Away logo
        painter->drawPixmap(V_TEAM_BOX_STARTX + awayLogoWidthOffset, V_TEAM_BOX_STARTY + awayLogoHeightOffset, *awayLogo);

        painter->setFont(awayName->font());
        QString aName;
        if (pitchingChange && !topOfInning) {
            aName = "PITCHING CHANGE";
            painter->setFont(QFont("Arail",18, QFont::Bold));
            painter->fillRect(V_TEAM_BOX_STARTX + LOGO_WIDTH, V_TEAM_BOX_STARTY, TEAM_BOX_WIDTH - LOGO_WIDTH, TEAM_BOX_HEIGHT, awayGradient );
            painter->drawText(V_TEAM_BOX_STARTX + 5 + LOGO_WIDTH, V_TEAM_BOX_STARTY, TEAM_NAME_WIDTH, TEAM_BOX_HEIGHT, Qt::AlignVCenter,
                              aName);
        }
        else {
            painter->setFont(awayRank->font());
            painter->setPen(QColor(255, 255, 255));
            painter->drawText(V_TEAM_BOX_STARTX + LOGO_WIDTH, V_TEAM_BOX_STARTY, awayRankOffset - LOGO_WIDTH, TEAM_BOX_HEIGHT, Qt::AlignCenter,  awayRank->toPlainText());
            painter->setFont(awayName->font());
            aName = awayName->toPlainText();
            painter->drawText(V_TEAM_BOX_STARTX + 5 + awayRankOffset, V_TEAM_BOX_STARTY, TEAM_NAME_WIDTH, TEAM_BOX_HEIGHT, Qt::AlignVCenter,
                              aName);
        }
        // Away Score
        //painter->fillRect(375, TEAM_BOX_Y, 78, 42, scoreGradient);

        painter->setFont(awayScore->font());
        painter->drawText(V_TEAM_BOX_STARTX + TEAM_NAME_WIDTH, V_TEAM_BOX_STARTY, SCORE_WIDTH, TEAM_BOX_HEIGHT,
                          Qt::AlignCenter, awayScore->toPlainText());
        // Home Text
        painter->fillRect(H_TEAM_BOX_STARTX, H_TEAM_BOX_STARTY, TEAM_BOX_WIDTH, TEAM_BOX_HEIGHT, homeGradient);
        painter->setPen(QColor(255,255,255));
        //painter->drawRect(H_TEAM_BOX_STARTX, H_TEAM_BOX_STARTY, TEAM_BOX_WIDTH, TEAM_BOX_HEIGHT);
        // Home logo

        painter->drawPixmap(H_TEAM_BOX_STARTX, H_TEAM_BOX_STARTY + homeLogoOffset, *homeLogo);

        painter->setFont(homeRank->font());
        painter->drawText(H_TEAM_BOX_STARTX + LOGO_WIDTH, H_TEAM_BOX_STARTY, homeRankOffset - LOGO_WIDTH, TEAM_BOX_HEIGHT, Qt::AlignCenter, homeRank->toPlainText());
        QString hName;
        if (pitchingChange && topOfInning) {
            hName = "PITCHING CHANGE";
            painter->setFont(QFont("Arail",18, QFont::Bold));
            painter->fillRect(H_TEAM_BOX_STARTX+ LOGO_WIDTH, H_TEAM_BOX_STARTY, TEAM_BOX_WIDTH - LOGO_WIDTH, TEAM_BOX_HEIGHT, homeGradient);
            painter->drawText(H_TEAM_BOX_STARTX + 5 + LOGO_WIDTH, H_TEAM_BOX_STARTY, TEAM_NAME_WIDTH, TEAM_BOX_HEIGHT, Qt::AlignVCenter,
                              hName);
        }
        else {
            painter->setFont(homeName->font());
            hName = homeName->toPlainText();
            painter->drawText(H_TEAM_BOX_STARTX + 5 + homeRankOffset, H_TEAM_BOX_STARTY, TEAM_NAME_WIDTH, TEAM_BOX_HEIGHT, Qt::AlignVCenter,
                              hName);
        }

        // Home Score
//        painter->fillRect(730, TEAM_BOX_Y, 78, 42, scoreGradient);

        painter->setFont(homeScore->font());
        painter->drawText(H_TEAM_BOX_STARTX + TEAM_NAME_WIDTH, H_TEAM_BOX_STARTY, SCORE_WIDTH, TEAM_BOX_HEIGHT, Qt::AlignCenter, homeScore->toPlainText());
        if (sponsor) {
            //StatBarText
            painter->fillRect(INNING_X, INNING_Y, SCOREBOARD_WIDTH,CLOCK_FIELD_HEIGHT, clockGradient);
            painter->setPen(QColor(255, 255, 255));
            painter->setFont(topBarText->font());
            painter->drawText(INNING_X, INNING_Y, SCOREBOARD_WIDTH,CLOCK_FIELD_HEIGHT, Qt::AlignCenter, topBarText->toPlainText());
        }
        painter->translate(DIAMOND_START + 20,40);
        // 3rd base
        painter->rotate(45);
        painter->setPen(QColor(1,1,1));
        if (thirdBase) {
            painter->fillRect(0, 0,26,26, topOfInning ? awayColor : homeColor);
        } else {
            painter->drawRect(0, 0,26,26);
        }
        // 1st base
        painter->rotate(-45);
        painter->translate(46,0);
        painter->rotate(45);
        if (firstBase) {
            painter->fillRect(0, 0,26,26, topOfInning ? awayColor : homeColor);
        } else {
            painter->drawRect(0, 0,26,26);
        }
        // 2nd base
        painter->rotate(-45);
        painter->translate(-23,-30);
        painter->rotate(45);
        if (secondBase) {
            painter->fillRect(0, 0,26,26, topOfInning ? awayColor : homeColor);
        } else {
            painter->drawRect(0, 0,26,26);
        }

    }
}

void
Scoreboard::prepareColor() {
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
    //awayGradient.setColorAt(0, end2);

    //mainGradient, clockGradient, ppGradient, scoreGradient
    //mainGradient.setColorAt(0, QColor(1,1,1));
    mainGradient.setColorAt(1, QColor(180,180,180));
    mainGradient.setColorAt(0, QColor(255,255,255));
    //mainGradient.setColorAt(.6, QColor(50,50,50));

    clockGradient.setColorAt(0, QColor(50,50,50));
    clockGradient.setColorAt(1, QColor(25,25,25));

    ppGradient.setColorAt(0, QColor(1,1,1));
    ppGradient.setColorAt(1, QColor(1,1,1));
    ppGradient.setColorAt(.45, QColor(50,50,50));
    ppGradient.setColorAt(.55, QColor(50,50,50));

    scoreGradient.setColorAt(0, QColor(1,1,1));
    scoreGradient.setColorAt(1, QColor(1,1,1));
    scoreGradient.setColorAt(.45, QColor(50,50,50));
    scoreGradient.setColorAt(.55, QColor(50,50,50));

}

void Scoreboard::prepareAwayName()
{
    int subtraction = 1;
    int fontPointSize = awayName->font().pointSize();
    QFontMetrics fontSize(awayName->font());
    while (fontSize.width(awayName->toPlainText()) > TEAM_NAME_WIDTH - awayRankOffset) {
        QFont tempFont("Arial", fontPointSize - subtraction, QFont::Bold);
        //topBarText->font().setPointSize(defaultSponsorText.pointSize()-subtraction);
        subtraction++;
        awayName->setFont(tempFont);
        QFontMetrics temp(awayName->font());
        fontSize = temp;
    }
}

void
Scoreboard::togglePitchingChange() {
    pitchingChange = !pitchingChange;
    scene()->update(x(), y(),SCOREBOARD_WIDTH,SCOREBOARD_HEIGHT);
}

void
Scoreboard::updateClock() {
    scene()->update(this->x() + COUNT_X, this->y(),  SCOREBOARD_WIDTH / 2, SCOREBOARD_HEIGHT);
}

void Scoreboard::updateCount(int b, int s, int o)
{
    count = QString::number(b) + "-" + QString::number(s);
    updateOut(o);
}

void Scoreboard::updateCount(int b, int s)
{
    count = QString::number(b) + "-" + QString::number(s);
    updateClock();
}

void Scoreboard::updateOut(int o)
{
    out = o;
    updateClock();
}

void Scoreboard::updateBases()
{
    scene()->update(x() + DIAMOND_START, y(), 32 * 3, SCOREBOARD_HEIGHT);
}

void Scoreboard::clearBases()
{
    firstBase = secondBase = thirdBase = false;
    updateBases();
}


void
Scoreboard::updateAwayScore(int score) {
    QString scoreText;
    awayScore->setPlainText(scoreText.setNum(score, 10));
    scene()->update(x() + V_TEAM_BOX_STARTX,y() + V_TEAM_BOX_STARTY,TEAM_BOX_WIDTH,TEAM_BOX_HEIGHT);
}

void
Scoreboard::updateHomeScore(int score) {
    QString str;
    homeScore->setPlainText(str.setNum(score, 10));
    scene()->update(x() + H_TEAM_BOX_STARTX,y() + H_TEAM_BOX_STARTY,TEAM_BOX_WIDTH,TEAM_BOX_HEIGHT);
}

void
Scoreboard::updateInning(QString mod, int pd) {
    topOfInning = (mod == "Top");
    QString periodStr = QString::number(pd);
//    if (periodStr.endsWith("11"))
//      periodStr += "th";
//    else if (periodStr.endsWith("1"))
//      periodStr += "st";
//    if (periodStr.endsWith("12"))
//      periodStr += "th";
//    else if (periodStr.endsWith("2"))
//      periodStr += "nd";
//    if (periodStr.endsWith("13"))
//      periodStr += "th";
//    else if (periodStr.endsWith("3"))
//      periodStr += "rd";
//    if (periodStr.endsWith("0") || periodStr.endsWith("4")
//      || periodStr.endsWith("5") || periodStr.endsWith("6")
//      || periodStr.endsWith("7") || periodStr.endsWith("8")
//      || periodStr.endsWith("9"))
//      periodStr += "th";
    inning = periodStr;
    scene()->update(x() + INNING_X, y() + INNING_Y, SCOREBOARD_WIDTH, CLOCK_FIELD_HEIGHT);
}

void
Scoreboard::showPd() {
    showPdAndClock = true;
    sponsor = false;
    scene()->update(x() + INNING_X, y() + INNING_Y, SCOREBOARD_WIDTH, CLOCK_FIELD_HEIGHT);
}

void
Scoreboard::final() {
    showPdAndClock = false;
    sponsor = false;
    centeredTimeText = "FINAL";
    scene()->update(x() + INNING_X, y() + INNING_Y, SCOREBOARD_WIDTH, CLOCK_FIELD_HEIGHT);
}

void
Scoreboard::changeTopBarText(QString text) {
    sponsor = true;
    topBarText->setPlainText(text);
    int subtraction = 1;
    topBarText->setFont(QFont("Arial", 18, QFont::Bold));
    QFontMetrics fontSize(topBarText->font());
    while (fontSize.width(text) > SCOREBOARD_WIDTH - 10) {
        QFont tempFont("Arial", defaultSponsorText.pointSize() - subtraction, QFont::Bold);
        subtraction++;
        topBarText->setFont(tempFont);
        QFontMetrics temp(topBarText->font());
        fontSize = temp;
    }
    scene()->update(x() + INNING_X, y() + INNING_Y,SCOREBOARD_WIDTH,CLOCK_FIELD_HEIGHT);
}

void
Scoreboard::displaySponsor() {
//    topBarText->setPlainText(sponsorText);
//    int subtraction = 1;
//    topBarText->setFont(defaultSponsorText);
//    QFontMetrics fontSize(topBarText->font());
//    while (fontSize.width(sponsorText) > SCOREBOARD_WIDTH - 10) {
//        QFont tempFont("Arial", defaultSponsorText.pointSize() - subtraction, QFont::Bold);
//        //topBarText->font().setPointSize(defaultSponsorText.pointSize()-subtraction);
//        subtraction++;
//        topBarText->setFont(tempFont);
//        QFontMetrics temp(topBarText->font());
//        fontSize = temp;
//    }
//    scene()->update(x(), y() + SPONSOR_BAR_Y,SCOREBOARD_WIDTH,SPONSOR_BAR_Y);
    sponsor=false;
     scene()->update(x() + INNING_X, y() + INNING_Y,SCOREBOARD_WIDTH,CLOCK_FIELD_HEIGHT);
}

void Scoreboard::toggleFirstBase(bool on)
{
    firstBase = on;
    updateBases();
}

void Scoreboard::toggleSecondBase(bool on)
{
    secondBase = on;
    updateBases();
}

void Scoreboard::toggleThirdBase(bool on)
{
    thirdBase = on;
    updateBases();
}
bool Scoreboard::getUseTransparency() const
{
    return useTransparency;
}

void Scoreboard::setUseTransparency(bool value)
{
    useTransparency = value;
}

int Scoreboard::getRealWidth()
{
    return SCOREBOARD_WIDTH;
}


void
Scoreboard::toggleShowBoard() {
    show = true;
    //if (useTransparency)
        //emit transparentField(x(), y()-49,SCOREBOARD_WIDTH,49);
    emit addNoTransparencyZone(QRect(x() + V_TEAM_BOX_STARTX, y() + V_TEAM_BOX_STARTY, LOGO_WIDTH, TEAM_BOX_HEIGHT));
    scene()->update(x(), y(), rect().width(), rect().height());
}

void Scoreboard::togglePpClocks()
{
    showPP = !showPP;
    scene()->update(this->x() + V_TEAM_BOX_STARTX - 3, this->y() + SCOREBOARD_HEIGHT,
                    SCOREBOARD_WIDTH - V_TEAM_BOX_STARTX, PP_BAR_HEIGHT);
}

void
Scoreboard::hideBoard() {
    if (show) {
        show = false;
        //emit removeTransparentField(x(), y()-49,SCOREBOARD_WIDTH,49);
        emit removeNoTransparencyZone(QRect(x() + V_TEAM_BOX_STARTX, y() + V_TEAM_BOX_STARTY, LOGO_WIDTH, TEAM_BOX_HEIGHT));
        scene()->update(x(), y(), rect().width(), rect().height());
    }
}

void
Scoreboard::delayed() {
    showPdAndClock = false;
    showClock = false;
    centeredTimeText = "DELAYED";
    scene()->update(x() + INNING_X, y() + INNING_Y, SCOREBOARD_WIDTH, CLOCK_FIELD_HEIGHT);
}

void
Scoreboard::displayClock() {
    showPdAndClock = true;
    showClock = true;
    scene()->update(x() + INNING_X, y() + INNING_Y, SCOREBOARD_WIDTH, CLOCK_FIELD_HEIGHT);
}
