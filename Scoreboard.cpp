#include "Scoreboard.h"
#include <QGraphicsScene>
#include <QMessageBox>
#include <QFontMetrics>
#include <QFontInfo>

#define GRADIENT_LEVEL .5
#define AWAY_PP 1
#define HOME_PP 2
#define NEUTRAL 3
#define TEAM_NAME_WIDTH 310
#define RANK_WIDTH 50
#define TEAM_BOX_Y 6
#define TEAM_BOX_HEIGHT 43
#define V_TEAM_BOX_STARTX 8
#define H_TEAM_BOX_STARTX 413
#define LOGO_WIDTH 50
#define SCOREBOARD_WIDTH 1246
#define CLOCK_FIELD_X 817
#define CLOCK_FIELD_WIDTH 342
#define DIAMOND_START (CLOCK_FIELD_WIDTH + CLOCK_FIELD_X + 10)
#define SCOREBOARD_HEIGHT 54
#define PP_BAR_HEIGHT 38

Scoreboard::Scoreboard(QColor awayCol, QColor homeCol, QString awayTeam, QString homeTeam,
                       QString sponsorText, /*Clock* clock,*/ QString pAwayRank, QString pHomeRank, QString pawayLogo) :
    homeColor(homeCol), awayColor(awayCol), emptyBase(QPixmap(":/images/GrayBase.png")),
    filledBase(QPixmap(":/images/YellowBase.png")) {
    QFont font("Arial", 34, QFont::Bold);
    QFont sponsorFont("Arial", 24, QFont::Bold);
#ifdef Q_OS_OSX
    font.setPointSize(40);
    sponsorFont.setPointSize(28);
    #endif

    defaultSponsorText = sponsorFont;
    show =firstBase = secondBase = thirdBase = false;
    setPixmap(QPixmap(":/images/Scoreboard.png"));
    ppBar = new QPixmap(":/images/ppBar.png");
    topBar = new QPixmap(":/images/ppBar.png");
    homeLogo = new QPixmap(":/images/M.png");
    awayLogo = new QPixmap(pawayLogo);
    inning = "1st";
    topOfInning = true;

    *homeLogo = homeLogo->scaledToHeight(TEAM_BOX_HEIGHT, Qt::SmoothTransformation);
    if (homeLogo->width() > LOGO_WIDTH)
        *homeLogo = homeLogo->scaledToWidth(LOGO_WIDTH, Qt::SmoothTransformation);
    homeLogoOffset = (TEAM_BOX_HEIGHT - homeLogo->height()) / 2;

    *awayLogo = awayLogo->scaledToHeight(TEAM_BOX_HEIGHT, Qt::SmoothTransformation);
    if (awayLogo->width() > LOGO_WIDTH)
        *awayLogo = awayLogo->scaledToWidth(LOGO_WIDTH, Qt::SmoothTransformation);
    awayLogoOffset = (TEAM_BOX_HEIGHT - awayLogo->height()) / 2;

    emptyBase = emptyBase.scaledToHeight(32, Qt::SmoothTransformation);
    filledBase = filledBase.scaledToHeight(32, Qt::SmoothTransformation);
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

    homeGradient.setStart(0, TEAM_BOX_Y);
    awayGradient.setStart(0, TEAM_BOX_Y);
    homeGradient.setFinalStop(0,TEAM_BOX_HEIGHT);
    awayGradient.setFinalStop(0,TEAM_BOX_HEIGHT);
    mainGradient.setStart(0,0);
    mainGradient.setFinalStop(0, SCOREBOARD_HEIGHT);
    clockGradient.setStart(0,3);
    clockGradient.setFinalStop(0, SCOREBOARD_HEIGHT - 3);
    ppGradient.setStart(0, SCOREBOARD_HEIGHT);
    ppGradient.setFinalStop(0, 92);
    scoreGradient.setStart(0, TEAM_BOX_Y);
    scoreGradient.setFinalStop(0, TEAM_BOX_Y + 44);
    prepareColor();
    // penalty gradient
    penaltyGradient.setStart(0, SCOREBOARD_HEIGHT);
    penaltyGradient.setFinalStop(0, SCOREBOARD_HEIGHT + PP_BAR_HEIGHT);
    penaltyGradient.setColorAt(0, QColor(255, 255, 0));
    penaltyGradient.setColorAt(1, QColor(188, 188, 0));

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
    sponsor = true;
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
        if (!useTransparency)
            painter->drawPixmap(0,-49,SCOREBOARD_WIDTH,49, *topBar);
        //painter->drawPixmap(0, 0, this->pixmap());
        painter->fillRect(0,0,SCOREBOARD_WIDTH, SCOREBOARD_HEIGHT, mainGradient);
        //painter->drawPixmap(34, 4, 66, 50, *homeLogo);
        //Clock - Game time...draw clock first since default color is black
        painter->setFont(QFont("Arial",28, QFont::Bold));
        painter->setPen(QColor(1,1,1));
        painter->fillRect(CLOCK_FIELD_X, 3, CLOCK_FIELD_WIDTH,48, clockGradient);
        if (showPdAndClock) {
            painter->drawText(CLOCK_FIELD_X, 3, CLOCK_FIELD_WIDTH/3, 48, Qt::AlignCenter, inning);
            painter->drawText(CLOCK_FIELD_X + CLOCK_FIELD_WIDTH/3, 3, CLOCK_FIELD_WIDTH/3, 48, Qt::AlignCenter,
                              count);
            painter->drawText(CLOCK_FIELD_X + CLOCK_FIELD_WIDTH*2/3, 3, CLOCK_FIELD_WIDTH/3, 48, Qt::AlignCenter,
                              QString::number(out) + " OUT");
            painter->fillRect(CLOCK_FIELD_X, topOfInning ? 3 : 48-3, CLOCK_FIELD_WIDTH/3, 3, QColor(231,231,28));

        }
        else {
            painter->drawText(CLOCK_FIELD_X, 3, CLOCK_FIELD_WIDTH, 48, Qt::AlignCenter, centeredTimeText);
        }
        painter->setFont(homeName->font());
        // Away text
        painter->setPen(QColor(255,255,255));
        painter->drawRect(V_TEAM_BOX_STARTX - 1, TEAM_BOX_Y - 1, TEAM_NAME_WIDTH + 79, 43);
        painter->fillRect(V_TEAM_BOX_STARTX, TEAM_BOX_Y, TEAM_NAME_WIDTH, 42, awayGradient );
        // Away logo
        painter->setOpacity(.99);
        painter->drawPixmap(V_TEAM_BOX_STARTX, TEAM_BOX_Y + awayLogoOffset, *awayLogo);
        painter->setOpacity(1);
        painter->setFont(awayRank->font());
        painter->setPen(QColor(255, 255, 255));
        painter->drawText(V_TEAM_BOX_STARTX + LOGO_WIDTH, TEAM_BOX_Y, awayRankOffset - LOGO_WIDTH, 42, Qt::AlignCenter,  awayRank->toPlainText());
        painter->setFont(awayName->font());
        painter->drawText(V_TEAM_BOX_STARTX + 3 + awayRankOffset, TEAM_BOX_Y, TEAM_NAME_WIDTH, 42, Qt::AlignVCenter, awayName->toPlainText());
        // Away Score
        //painter->fillRect(375, TEAM_BOX_Y, 78, 42, scoreGradient);
        painter->drawPixmap(V_TEAM_BOX_STARTX + TEAM_NAME_WIDTH, TEAM_BOX_Y, 78, 42, *ppBar);
        painter->setFont(awayScore->font());
        painter->drawText(V_TEAM_BOX_STARTX + TEAM_NAME_WIDTH, TEAM_BOX_Y, 78, 42,
                          Qt::AlignCenter, awayScore->toPlainText());
        // Home Text
        painter->setPen(QColor(255,255,255));
        painter->drawRect(H_TEAM_BOX_STARTX - 1, TEAM_BOX_Y - 1, TEAM_NAME_WIDTH + 79, 43);
        painter->fillRect(H_TEAM_BOX_STARTX, TEAM_BOX_Y, TEAM_NAME_WIDTH, 42, homeGradient);
        // Home logo
        painter->setOpacity(.99);
        painter->drawPixmap(H_TEAM_BOX_STARTX, TEAM_BOX_Y + homeLogoOffset, *homeLogo);
        painter->setOpacity(1);
        painter->setFont(homeRank->font());
        painter->drawText(H_TEAM_BOX_STARTX + LOGO_WIDTH, TEAM_BOX_Y, homeRankOffset - LOGO_WIDTH, 42, Qt::AlignCenter, homeRank->toPlainText());
        painter->setFont(homeName->font());
        painter->drawText(H_TEAM_BOX_STARTX + 5 + homeRankOffset, TEAM_BOX_Y, TEAM_NAME_WIDTH, 42, Qt::AlignVCenter, homeName->toPlainText());
        // Home Score
//        painter->fillRect(730, TEAM_BOX_Y, 78, 42, scoreGradient);
        painter->drawPixmap(H_TEAM_BOX_STARTX + TEAM_NAME_WIDTH, TEAM_BOX_Y, 78, 42, *ppBar);
        painter->setFont(homeScore->font());
        painter->drawText(H_TEAM_BOX_STARTX + TEAM_NAME_WIDTH, TEAM_BOX_Y, 78, 42, Qt::AlignCenter, homeScore->toPlainText());
        if (sponsor) {
            //StatBarText
            painter->setPen(QColor(255, 255, 255));
            painter->setFont(topBarText->font());
            painter->drawText(0,-49,SCOREBOARD_WIDTH,49, Qt::AlignCenter, topBarText->toPlainText());
        }

        if (pitchingChange) {
            painter->setPen(QColor(255, 255, 255));
            painter->setFont(defaultSponsorText);
            painter->drawPixmap(CLOCK_FIELD_X,SCOREBOARD_HEIGHT,CLOCK_FIELD_WIDTH,PP_BAR_HEIGHT, *ppBar );
            painter->drawText(CLOCK_FIELD_X + 8, SCOREBOARD_HEIGHT, CLOCK_FIELD_WIDTH, PP_BAR_HEIGHT, Qt::AlignLeft | Qt::AlignVCenter, "PITCHING CHANGE");
        }
        painter->drawPixmap(DIAMOND_START, 20, 32, 32, thirdBase ? filledBase : emptyBase);
        painter->drawPixmap(DIAMOND_START + 17, 0, 32, 32, secondBase ? filledBase : emptyBase);
        painter->drawPixmap(DIAMOND_START + 34, 20, 32, 32, firstBase ? filledBase : emptyBase);
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

    //mainGradient, clockGradient, ppGradient, scoreGradient
    mainGradient.setColorAt(0, QColor(1,1,1));
    mainGradient.setColorAt(1, QColor(1,1,1));
    mainGradient.setColorAt(.4, QColor(156,0,0));
    mainGradient.setColorAt(.6, QColor(156,0,0));

    clockGradient.setColorAt(0, QColor(255,255,255));
    clockGradient.setColorAt(1, QColor(255,255,255));
    clockGradient.setColorAt(.45, QColor(180,180,180));
    clockGradient.setColorAt(.55, QColor(180,180,180));

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
    scene()->update();
}

void
Scoreboard::updateClock() {
    scene()->update(this->x() + CLOCK_FIELD_X, this->y() + 3, CLOCK_FIELD_WIDTH, 50);
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
    scene()->update(x() + DIAMOND_START, y(), 32 * 3, SCOREBOARD_WIDTH);
}


void
Scoreboard::updateAwayScore(int score) {
    QString scoreText;
    awayScore->setPlainText(scoreText.setNum(score, 10));
    scene()->update();
}

void
Scoreboard::updateHomeScore(int score) {
    QString str;
    homeScore->setPlainText(str.setNum(score, 10));
    scene()->update();
}

void
Scoreboard::updateInning(QString mod, int pd) {
    topOfInning = mod == "Top";
    QString periodStr = QString::number(pd);
    if (periodStr.endsWith("11"))
      periodStr += "th";
    else if (periodStr.endsWith("1"))
      periodStr += "st";
    if (periodStr.endsWith("12"))
      periodStr += "th";
    else if (periodStr.endsWith("2"))
      periodStr += "nd";
    if (periodStr.endsWith("13"))
      periodStr += "th";
    else if (periodStr.endsWith("3"))
      periodStr += "rd";
    if (periodStr.endsWith("0") || periodStr.endsWith("4")
      || periodStr.endsWith("5") || periodStr.endsWith("6")
      || periodStr.endsWith("7") || periodStr.endsWith("8")
      || periodStr.endsWith("9"))
      periodStr += "th";
    inning = periodStr;
    scene()->update(x() + CLOCK_FIELD_X, y(), CLOCK_FIELD_WIDTH, SCOREBOARD_HEIGHT);
}

void
Scoreboard::showPd() {
    showPdAndClock = true;
    scene()->update(x() + CLOCK_FIELD_X, y(), CLOCK_FIELD_WIDTH, SCOREBOARD_HEIGHT);
}

void
Scoreboard::final() {
    showPdAndClock = false;
    centeredTimeText = "FINAL";
    scene()->update(x() + CLOCK_FIELD_X, y(), CLOCK_FIELD_WIDTH, SCOREBOARD_HEIGHT);
}

void
Scoreboard::changeTopBarText(QString text) {
    topBarText->setPlainText(text);
    int subtraction = 1;
    topBarText->setFont(QFont("Arial", 34, QFont::Bold));
    QFontMetrics fontSize(topBarText->font());
    while (fontSize.width(text) > SCOREBOARD_WIDTH - 10) {
        QFont tempFont("Arial", defaultSponsorText.pointSize() - subtraction, QFont::Bold);
        subtraction++;
        topBarText->setFont(tempFont);
        QFontMetrics temp(topBarText->font());
        fontSize = temp;
    }
    scene()->update(x(), y()-49,SCOREBOARD_WIDTH,49);
}

void
Scoreboard::displaySponsor() {
    topBarText->setPlainText(sponsorText);
    int subtraction = 1;
    topBarText->setFont(defaultSponsorText);
    QFontMetrics fontSize(topBarText->font());
    while (fontSize.width(sponsorText) > SCOREBOARD_WIDTH - 10) {
        QFont tempFont("Arial", defaultSponsorText.pointSize() - subtraction, QFont::Bold);
        //topBarText->font().setPointSize(defaultSponsorText.pointSize()-subtraction);
        subtraction++;
        topBarText->setFont(tempFont);
        QFontMetrics temp(topBarText->font());
        fontSize = temp;
    }
    scene()->update(x(), y()-49,SCOREBOARD_WIDTH,49);
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
    if (useTransparency)
        emit transparentField(x(), y()-49,SCOREBOARD_WIDTH,49);
    scene()->update();
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
        emit removeTransparentField(x(), y()-49,SCOREBOARD_WIDTH,49);
        scene()->update();
    }
}

void
Scoreboard::delayed() {
    showPdAndClock = false;
    showClock = false;
    centeredTimeText = "DELAYED";
    scene()->update(x() + CLOCK_FIELD_X, y(), CLOCK_FIELD_WIDTH, SCOREBOARD_HEIGHT);
}

void
Scoreboard::displayClock() {
    showPdAndClock = true;
    showClock = true;
    scene()->update(x() + CLOCK_FIELD_X, y(), CLOCK_FIELD_WIDTH, SCOREBOARD_HEIGHT);
}
