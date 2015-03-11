#include "BaseballGame.h"
#include "SeasonXMLHandler.h"
#include "GameXmlHandler.h"
#include "ClockDialog.h"


BaseballGame::BaseballGame(QString awayName, QString homeName, QColor awayColor, QColor homeColor,
                       QString awayXML, QString homeXML, QString sponsor, QString announcers,
                       QString awayRank, QString homeRank, int screenWidth, QString awayLogo) :
    awayName(awayName), homeName(homeName), sponsor(sponsor), announcers(announcers), awayColor(awayColor),
    homeColor(homeColor), awayRank(awayRank), homeRank(homeRank),
    sb(awayColor, homeColor, awayName, homeName, sponsor, /*&gameClock,*/ awayRank, homeRank, awayLogo),
    lt (awayColor, homeColor, screenWidth) {
    isFinal = false;
    awayScore = 0;
    homeScore = 0;
    homeHits = 0;
    awayHits = 0;
    period = 0;
    awayErrors = 0;
    homeErrors = 0;
    inningMod = "Bot";
    //connect(&gameClock, SIGNAL(clockExpired()), this, SLOT(toggleClock()));
    //connect(&timer, SIGNAL(timeout()), &gameClock, SLOT(tick()));

    //connect(this, SIGNAL(periodChanged(int)), &sb, SLOT(updatePeriod(int)));
    connect(this, SIGNAL(awayScoreChanged(int)), &sb, SLOT(updateAwayScore(int)));
    connect(this, SIGNAL(homeScoreChanged(int)), &sb, SLOT(updateHomeScore(int)));

    // Make teams...
    homeTeam = new BaseballTeam();
    awayTeam = new BaseballTeam();

    SeasonXMLHandler handler(homeTeam);
    QXmlSimpleReader r;
    r.setContentHandler(&handler);
    r.setErrorHandler(&handler);
    QFile file(homeXML);
    QXmlInputSource src(&file);
    r.parse(src);

    SeasonXMLHandler roadHandler(awayTeam);
    r.setContentHandler(&roadHandler);
    r.setErrorHandler(&roadHandler);
    QFile f2(awayXML);
    QXmlInputSource src2(&f2);
    r.parse(src2);
}

void
BaseballGame::awayScored(int score) {
    awayScore += score;
    emit awayScoreChanged(awayScore);
}

void
BaseballGame::subRunAway() {
    awayScore --;
    emit awayScoreChanged(awayScore);
}

void
BaseballGame::homeScored(int score) {
    homeScore += score;
    emit homeScoreChanged(homeScore);
}

void
BaseballGame::subRunHome() {
    homeScore --;
    emit homeScoreChanged(homeScore);
}

void
BaseballGame::addAwayHit() {
    awayHits++;
    emit awayHitsChanged(awayHits);
}

void
BaseballGame::subAwayHit() {
    awayHits--;
    emit awayHitsChanged(awayHits);
}

void
BaseballGame::showAnnouncers() {
    if (announcers.contains("and") || announcers.contains("&")) {
        sb.changeTopBarText("Commentators: " + announcers);
    }
    else {
        sb.changeTopBarText("Commentator: " + announcers);
    }
}

void BaseballGame::gatherHomeSeasonStatsLt(int index)
{
    QList<QString> labels, numbers;
    BaseballPlayer* player = getHomeTeam()->getPlayer(index);
    labels.append("GP");
    numbers.append(QString::number(player->getGp()));

    lt.prepareForDisplay(player->getName(), player->getUni(), player->getYear(),
                         labels, numbers, true);
}

void BaseballGame::gatherHomeSeasonStatsSb(int index)
{
    BaseballPlayer* player = getHomeTeam()->getPlayer(index);
    QString text = player->getName() + " (" + getHomeName()+"): ";

    sb.changeTopBarText(text);
}

void BaseballGame::gatherHomeGameStatsLt(int index)
{
    BaseballPlayer* player = getHomeTeam()->getPlayer(index);
    QList<QString> labels, numbers;

    lt.prepareForDisplay(player->getName(), player->getUni(), player->getYear(),
                         labels, numbers, true);
}

void BaseballGame::gatherAwayGameStatsLt(int index)
{
    BaseballPlayer* player = getAwayTeam()->getPlayer(index);
    QList<QString> labels, numbers;

    lt.prepareForDisplay(player->getName(), player->getUni(), "",
                         labels, numbers, false);
}

void BaseballGame::gatherHomeGameStatsSb(int index)
{
    BaseballPlayer* player = getHomeTeam()->getPlayer(index);
    QString text = player->getName() + " (" + getHomeName()+"): ";

    sb.changeTopBarText(text);
}

void BaseballGame::gatherAwaySeasonStatsLt(int index)
{

}

void BaseballGame::gatherAwaySeasonStatsSb(int index)
{

}

void BaseballGame::gatherAwayGameStatsSb(int index)
{
    BaseballPlayer* player = getAwayTeam()->getPlayer(index);
    QString text = player->getName() + " (" + getAwayName()+"): ";

    sb.changeTopBarText(text);
}

/*
Clock* BaseballGame::getGameClock()
{
    return &gameClock;
}
*/
BaseballTeam* BaseballGame::getAwayTeam() const
{
    return awayTeam;
}

BaseballTeam* BaseballGame::getHomeTeam() const
{
    return homeTeam;
}


QString BaseballGame::getAwayName() const
{
    return awayName;
}

void BaseballGame::setAwayName(const QString& value)
{
    awayName = value;
}

QString BaseballGame::getHomeName() const
{
    return homeName;
}

void BaseballGame::setHomeName(const QString& value)
{
    homeName = value;
}

QString BaseballGame::getAnnouncers() const
{
    return announcers;
}

void BaseballGame::setAnnouncers(const QString& value)
{
    announcers = value;
}

QString BaseballGame::getSponsor() const
{
    return sponsor;
}

void BaseballGame::setSponsor(const QString& value)
{
    sponsor = value;
}

LowerThird* BaseballGame::getLt()
{
    return &lt;
}


Scoreboard* BaseballGame::getSb()
{
    return &sb;
}

void
BaseballGame::addHomeHit() {
    homeHits++;
    emit homeHitsChanged(homeHits);
}

void
BaseballGame::subHomeHit() {
    homeHits--;
    emit homeHitsChanged(homeHits);
}

void
BaseballGame::advancePeriod() {
    if (inningMod == "Top")
        inningMod = "Bot";
    else {
        inningMod = "Top";
        period++;
    }
    isFinal = false;
    balls = 0;
    strikes = 0;
    outs = 0;
    emit ballsChanged(balls);
    emit strikesChanged(strikes);
    emit outsChanged(outs);
    emit periodChanged(inningMod, period);
}

void
BaseballGame::rewindPeriod() {
    if (inningMod == "Top") {
        inningMod = "Bot";
        period--;
    }
    else {
        inningMod = "Top";
    }
    isFinal = false;
    emit periodChanged(inningMod, period);
}

void BaseballGame::makeFinal()
{
    isFinal = true;
}
int BaseballGame::getOuts() const
{
    return outs;
}

void BaseballGame::setOuts(int value)
{
    outs = value;
}

int BaseballGame::getBalls() const
{
    return balls;
}

void BaseballGame::setBalls(int value)
{
    balls = value;
}

int BaseballGame::getStrikes() const
{
    return strikes;
}

void BaseballGame::setStrikes(int value)
{
    strikes = value;
}

int BaseballGame::getAwayBatter() const
{
    return awayBatter;
}

void BaseballGame::setAwayBatter(int value)
{
    awayBatter = value;
}

int BaseballGame::getHomeBatter() const
{
    return homeBatter;
}

void BaseballGame::setHomeBatter(int value)
{
    homeBatter = value;
}


int BaseballGame::getAwayErrors() const
{
    return awayErrors;
}

void BaseballGame::setAwayErrors(int value)
{
    awayErrors = value;
}

int BaseballGame::getHomeErrors() const
{
    return homeErrors;
}

void BaseballGame::setHomeErrors(int value)
{
    homeErrors = value;
}

int BaseballGame::getAwayHits() const
{
    return awayHits;
}

void BaseballGame::setAwayHits(int value)
{
    awayHits = value;
}

int BaseballGame::getHomeHits() const
{
    return homeHits;
}

void BaseballGame::setHomeHits(int value)
{
    homeHits = value;
}

bool BaseballGame::getIsFinal() const
{
    return isFinal;
}

void BaseballGame::setIsFinal(bool value)
{
    isFinal = value;
}

int BaseballGame::getPeriod() const
{
    return period;
}

void BaseballGame::setPeriod(int value)
{
    period = value;
}

int BaseballGame::getHomeScore() const
{
    return homeScore;
}

void BaseballGame::setHomeScore(int value)
{
    homeScore = value;
}

int BaseballGame::getAwayScore() const
{
    return awayScore;
}

void BaseballGame::setAwayScore(int value)
{
    awayScore = value;
}

QColor BaseballGame::getAwayColor() const
{
    return awayColor;
}

void BaseballGame::setAwayColor(const QColor& value)
{
    awayColor = value;
}

QColor BaseballGame::getHomeColor() const
{
    return homeColor;
}

void BaseballGame::setHomeColor(const QColor& value)
{
    homeColor = value;
}

QString BaseballGame::getAwayRank() const
{
    return awayRank;
}

void BaseballGame::setAwayRank(const QString& value)
{
    awayRank = value;
}

QString BaseballGame::getHomeRank() const
{
    return homeRank;
}

void BaseballGame::setHomeRank(const QString& value)
{
    homeRank = value;
}

/*void
BaseballGame::toggleClock() {
    clockRunning = !clockRunning;
    if (clockRunning) {
        timer.start();
    }
    else {
        timer.stop();
    }
    emit clockIsRunning(clockRunning);
}
*/
