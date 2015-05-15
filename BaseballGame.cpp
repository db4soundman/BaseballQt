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
    awayBatter = homeBatter= 0;
    awayScore = 0;
    homeScore = 0;
    homeHits = 0;
    awayHits = 0;
    period = 0;
    awayErrors = 0;
    homeErrors = 0;
    onFirst = onSecond = onThird = false;
    inningMod = "Bot";
    //connect(&gameClock, SIGNAL(clockExpired()), this, SLOT(toggleClock()));
    //connect(&timer, SIGNAL(timeout()), &gameClock, SLOT(tick()));

    connect(this, SIGNAL(periodChanged(QString,int)), &sb, SLOT(updateInning(QString,int)));
    connect(this, SIGNAL(awayScoreChanged(int)), &sb, SLOT(updateAwayScore(int)));
    connect(this, SIGNAL(homeScoreChanged(int)), &sb, SLOT(updateHomeScore(int)));
    connect(this, SIGNAL(firstBaseStatus(bool)), &sb, SLOT(toggleFirstBase(bool)));
    connect(this, SIGNAL(secondBaseStatus(bool)), &sb, SLOT(toggleSecondBase(bool)));
    connect(this, SIGNAL(thirdBaseStatus(bool)), &sb, SLOT(toggleThirdBase(bool)));
    connect(this, SIGNAL(basesCleared()), &sb, SLOT(clearBases()));
    connect(this, SIGNAL(updateCount(int,int,int)), &sb, SLOT(updateCount(int,int,int)));

    // Make teams...
    homeTeam = new BaseballTeam();
    awayTeam = new BaseballTeam();

    connect(homeTeam, SIGNAL(battingOrderChanged()),
            this, SLOT(updateBatterNoAdvance()));
    connect(awayTeam, SIGNAL(battingOrderChanged()),
            this, SLOT(updateBatterNoAdvance()));

    SeasonXMLHandler handler(homeTeam);
    QXmlSimpleReader r;
    r.setContentHandler(&handler);
    r.setErrorHandler(&handler);
    QFile file(homeXML);
    QXmlInputSource src(&file);
    r.parse(src);

    BaseballPlayer* currPlayer = new BaseballPlayer();
    currPlayer->setName("NO NAME");
    currPlayer->setUni("");
    currPlayer->setYear("");
    currPlayer->setGp(0);
    currPlayer->setSacFly(0);
    currPlayer->setHbp(0);
    currPlayer->setStrikeouts(0);
    currPlayer->setWalks(0);
    currPlayer->setHr(0);
    currPlayer->setTriples(0);
    currPlayer->setDoubles(0);
    currPlayer->setRbi(0);
    currPlayer->setAb(0);
    currPlayer->setAp(0);
    currPlayer->setGs(0);
    currPlayer->setSaves(0);
    currPlayer->setWins(0);
    currPlayer->setLosses(0);
    currPlayer->setHitsAllowed(0);
    currPlayer->setRunsAllowed(0);
    currPlayer->setEr(0);
    currPlayer->setBb(0);
    currPlayer->setKOut(0);
    homeTeam->addPlayer(currPlayer);

    SeasonXMLHandler roadHandler(awayTeam);
    r.setContentHandler(&roadHandler);
    r.setErrorHandler(&roadHandler);
    QFile f2(awayXML);
    QXmlInputSource src2(&f2);
    r.parse(src2);

    currPlayer = new BaseballPlayer();
    currPlayer->setName("NO NAME");
    currPlayer->setUni("");
    currPlayer->setYear("");
    currPlayer->setGp(0);
    currPlayer->setSacFly(0);
    currPlayer->setHbp(0);
    currPlayer->setStrikeouts(0);
    currPlayer->setWalks(0);
    currPlayer->setHr(0);
    currPlayer->setTriples(0);
    currPlayer->setDoubles(0);
    currPlayer->setRbi(0);
    currPlayer->setAb(0);
    currPlayer->setAp(0);
    currPlayer->setGs(0);
    currPlayer->setSaves(0);
    currPlayer->setWins(0);
    currPlayer->setLosses(0);
    currPlayer->setHitsAllowed(0);
    currPlayer->setRunsAllowed(0);
    currPlayer->setEr(0);
    currPlayer->setBb(0);
    currPlayer->setKOut(0);
    awayTeam->addPlayer(currPlayer);
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

void BaseballGame::checkOuts()
{
    if (outs >= 3) {
        advancePeriod();
    }
}

BaseballPlayer *BaseballGame::getPitcher()
{
    if (inningMod == "Top") {
        return homeTeam->getPitcher();
    }
    return awayTeam->getPitcher();
}

BaseballPlayer *BaseballGame::getBatter()
{
    if (inningMod == "Top") {
        return awayTeam->getBatterByIndex(awayBatter);
    }
    return homeTeam->getBatterByIndex(homeBatter);
}

void
BaseballGame::showAnnouncers() {
    if (announcers.contains(" and ") || announcers.contains("&")) {
        sb.changeTopBarText("Commentators: " + announcers);
    }
    else {
        sb.changeTopBarText("Commentator: " + announcers);
    }
}

void BaseballGame::gatherBatterGraphic()
{
     BaseballPlayer* player = getBatter();
     QList<QString> labels, numbers;

     labels.append("GP");
     labels.append("AVG");
     labels.append("RBI");
     labels.append("HR");
     labels.append("BB");
     labels.append("SO");

     numbers.append(QString::number(player->getGp()));
     numbers.append(player->getAvg());
     numbers.append(QString::number(player->getRbi()));
     numbers.append(QString::number(player->getHr()));
     numbers.append(QString::number(player->getWalks()));
     numbers.append(QString::number(player->getStrikeouts()));

     lt.prepareForDisplay(player->getName(),player->getUni(), player->getPos(),
                          labels, numbers, inningMod == "Bot");
}

void BaseballGame::gatherBatterSeasonSb()
{
     BaseballPlayer* player = getBatter();
     QString text = player->getName() + " (" +
             inningMod == "Top" ? getAwayName() : getHomeName()+"): ";
     text += player->getAvg() + ", " + QString::number(player->getWalks()) + " BB, "+
             QString::number(player->getStrikeouts()) + " K";
     sb.changeTopBarText(text);
}

void BaseballGame::gatherHomePitcherRecapLt()
{
    QList<QString> labels, numbers;
    BaseballPlayer* player = homeTeam->getPitcher();
    labels.append("IP");
    labels.append("PC");
    labels.append("B");
    labels.append("S");
    labels.append("BB");
    labels.append("K");

    numbers.append(player->getIpToday());
    numbers.append(QString::number(player->getPitchCount()));
    numbers.append(QString::number(player->getBallsThrown()));
    numbers.append(QString::number(player->getStrikesThrown()));
    numbers.append(QString::number(player->getPWalksToday()));
    numbers.append(QString::number(player->getPStrikeOutsToday()));

    lt.prepareForDisplay(player->getName(), player->getUni(), "P",
                         labels, numbers, true);
}

void BaseballGame::gatherAwayPitcherRecapLt()
{
    QList<QString> labels, numbers;
    BaseballPlayer* player = awayTeam->getPitcher();
    labels.append("IP");
    labels.append("PC");
    labels.append("B");
    labels.append("S");
    labels.append("BB");
    labels.append("K");

    numbers.append(player->getIpToday());
    numbers.append(QString::number(player->getPitchCount()));
    numbers.append(QString::number(player->getBallsThrown()));
    numbers.append(QString::number(player->getStrikesThrown()));
    numbers.append(QString::number(player->getPWalksToday()));
    numbers.append(QString::number(player->getPStrikeOutsToday()));

    lt.prepareForDisplay(player->getName(), player->getUni(), "P",
                         labels, numbers, false);
}

void BaseballGame::gatherHomePitcherSb()
{
    BaseballPlayer* player = getHomeTeam()->getPitcher();
    QString text = player->getName() + " (" + getHomeName()+"): ";
    text += QString::number(player->getPitchCount()) + " PITCHES, " + QString::number(player->getBallsThrown()) + " BALLS, "+
            QString::number(player->getStrikesThrown()) + " STRIKES";

    sb.changeTopBarText(text);
}

void BaseballGame::gatherAwayPitcherSb()
{
    BaseballPlayer* player = getAwayTeam()->getPitcher();
    QString text = player->getName() + " (" + getAwayName()+"): ";
    text += QString::number(player->getPitchCount()) + " PITCHES, " + QString::number(player->getBallsThrown()) + " BALLS, "+
            QString::number(player->getStrikesThrown()) + " STRIKES";

    sb.changeTopBarText(text);
}

void BaseballGame::gatherHomeSeasonStatsLt(int index)
{
    QList<QString> labels, numbers;
    BaseballPlayer* player = getHomeTeam()->getPlayer(index);
    labels.append("GP");
    labels.append("AVG");
    labels.append("RBI");
    labels.append("HR");
    labels.append("BB");
    labels.append("SO");

    numbers.append(QString::number(player->getGp()));
    numbers.append(player->getAvg());
    numbers.append(QString::number(player->getRbi()));
    numbers.append(QString::number(player->getHr()));
    numbers.append(QString::number(player->getWalks()));
    numbers.append(QString::number(player->getStrikeouts()));

    lt.prepareForDisplay(player->getName(), player->getUni(), player->getYear(),
                         labels, numbers, true);
}

void BaseballGame::gatherHomeSeasonStatsSb(int index)
{
    BaseballPlayer* player = getHomeTeam()->getPlayer(index);
    QString text = player->getName() + " (" + getHomeName()+"): ";
    text += player->getAvg() + ", " + QString::number(player->getWalks()) + " BB, "+
            QString::number(player->getStrikeouts()) + " K";

    sb.changeTopBarText(text);
}

void BaseballGame::gatherHomeGameStatsLt(int index)
{
    BaseballPlayer* player = getHomeTeam()->getPlayer(index);
    QList<QString> labels, numbers;

    labels.append("H");
    labels.append("AB");
    labels.append("RBI");
    labels.append("BB");
    labels.append("SO");

    numbers.append(QString::number(player->getHToday()));
    numbers.append(QString::number(player->getAbToday()));
    numbers.append(QString::number(player->getRbiToday()));
    numbers.append(QString::number(player->getWalksToday()));
    numbers.append(QString::number(player->getStrikeoutsToday()));

    lt.prepareForDisplay(player->getName(), player->getUni(), player->getYear(),
                         labels, numbers, true);
}

void BaseballGame::gatherAwayGameStatsLt(int index)
{
    BaseballPlayer* player = getAwayTeam()->getPlayer(index);
    QList<QString> labels, numbers;
    labels.append("H");
    labels.append("AB");
    labels.append("RBI");
    labels.append("BB");
    labels.append("SO");

    numbers.append(QString::number(player->getHToday()));
    numbers.append(QString::number(player->getAbToday()));
    numbers.append(QString::number(player->getRbiToday()));
    numbers.append(QString::number(player->getWalksToday()));
    numbers.append(QString::number(player->getStrikeoutsToday()));
    lt.prepareForDisplay(player->getName(), player->getUni(), player->getUni(),
                         labels, numbers, false);
}

void BaseballGame::gatherHomeGameStatsSb(int index)
{
    BaseballPlayer* player = getHomeTeam()->getPlayer(index);
    QString text = player->getName() + " (" + getHomeName()+"): ";

   // sb.changeTopBarText(text);
}

void BaseballGame::gatherAwaySeasonStatsLt(int index)
{
    QList<QString> labels, numbers;
    BaseballPlayer* player = getAwayTeam()->getPlayer(index);
    labels.append("GP");
    labels.append("AVG");
    labels.append("RBI");
    labels.append("HR");
    labels.append("BB");
    labels.append("SO");

    numbers.append(QString::number(player->getGp()));
    numbers.append(player->getAvg());
    numbers.append(QString::number(player->getRbi()));
    numbers.append(QString::number(player->getHr()));
    numbers.append(QString::number(player->getWalks()));
    numbers.append(QString::number(player->getStrikeouts()));

    lt.prepareForDisplay(player->getName(), player->getUni(), player->getYear(),
                         labels, numbers, false);
}

void BaseballGame::gatherAwaySeasonStatsSb(int index)
{
    BaseballPlayer* player = getAwayTeam()->getPlayer(index);
    QString text = player->getName() + " (" + getAwayName()+"): ";
    text += player->getAvg() + ", " + QString::number(player->getWalks()) + " BB, "+
            QString::number(player->getStrikeouts()) + " K";

    sb.changeTopBarText(text);
}

void BaseballGame::gatherAwayGameStatsSb(int index)
{
    BaseballPlayer* player = getAwayTeam()->getPlayer(index);
    QString text = player->getName() + " (" + getAwayName()+"): ";

   // sb.changeTopBarText(text);
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
    clearBases();
    //clearCount();
    balls = strikes = 0;
    outs = 0;
    emit updateCount(balls, strikes, outs);
    emit periodChanged(inningMod, period);
    updateBatterNoAdvance();
    emit pitchCountUpdate(getPitcher()->getName() + ": " + getPitcher()->getTodaysPitchCount());
}

void
BaseballGame::rewindPeriod() {
    if (inningMod == "Top") {
        inningMod = "Bot";
        period--;
        emit batterChanged(homeTeam->getBatterByIndex(homeBatter)->getName());
    }
    else {
        inningMod = "Top";
        emit batterChanged(awayTeam->getBatterByIndex(awayBatter)->getName());
    }
    isFinal = false;
    balls = strikes = 0;
    outs = 0;
    emit updateCount(balls, strikes, outs);
    emit periodChanged(inningMod, period);
    updateBatterNoAdvance();
    emit pitchCountUpdate(getPitcher()->getName() + ": " + getPitcher()->getTodaysPitchCount());
}

void BaseballGame::addScore(int value)
{
    if (inningMod == "Top") {
        awayScore += value;
        emit awayScoreChanged(awayScore);
    }
    else {
        homeScore += value;
        emit homeScoreChanged(homeScore);
    }
}

void BaseballGame::addHit()
{
    if (inningMod == "Top") {
        awayHits++;
        emit awayHitsChanged(awayHits);
    }
    else {
        homeHits++;
        emit homeHitsChanged(homeHits);
    }
}

void BaseballGame::subHit()
{
    if (inningMod == "Top") {
        awayHits--;
        emit awayHitsChanged(awayHits);
    }
    else {
        homeHits--;
        emit homeHitsChanged(homeHits);
    }
}

void BaseballGame::addError()
{
    if (inningMod != "Top") {
        awayErrors++;
        emit awayErrorsChanged(awayErrors);
    }
    else {
        homeErrors++;
        emit homeErrorsChanged(homeErrors);
    }
}

void BaseballGame::subError()
{
    if (inningMod == "Top") {
        awayErrors--;
        emit awayErrorsChanged(awayErrors);
    }
    else {
        homeErrors--;
        emit homeErrorsChanged(homeErrors);
    }
}

void BaseballGame::makeFinal()
{
    isFinal = true;
}

void BaseballGame::advanceBatter()
{
    if (inningMod == "Top") {
        awayBatter = (awayBatter + 1) % 9;
        emit batterChanged(awayTeam->getBatterByIndex(awayBatter)->getName());
    }
    else {
        homeBatter = (homeBatter + 1) % 9;
        emit batterChanged(homeTeam->getBatterByIndex(homeBatter)->getName());
    }
}

void BaseballGame::updateBatterNoAdvance()
{
    if (inningMod == "Top") {
        emit batterChanged(awayTeam->getBatterByIndex(awayBatter)->getName());
    }
    else {
        emit batterChanged(homeTeam->getBatterByIndex(homeBatter)->getName());
    }
}

void BaseballGame::updateFirstBaseStatus()
{
    onFirst = !onFirst;
    emit firstBaseStatus(onFirst);
}

void BaseballGame::updateSecondBaseStatus()
{
    onSecond = !onSecond;
    emit secondBaseStatus(onSecond);
}

void BaseballGame::updateThirdBaseStatus()
{
    onThird = !onThird;
    emit thirdBaseStatus(onThird);
}

void BaseballGame::clearBases()
{
    onFirst = onSecond = onThird = false;
    emit basesCleared();
}

void BaseballGame::decideTeamForDefense()
{
    if (inningMod == "Top") {
        emit showDefense(true);
    }
    else emit showDefense(false);
}

void BaseballGame::decideTeamForBattingOrder()
{
    if (inningMod != "Top") {
        emit showBatters(true);
    }
    else emit showBatters(false);
}

void BaseballGame::ballThrown()
{
    BaseballPlayer* pitcher = getPitcher();
    pitcher->ballThrown(1);
    balls++;
    emit updateCount(balls, strikes, outs);
    emit pitchCountUpdate(pitcher->getName() + ": " + pitcher->getTodaysPitchCount());
}

void BaseballGame::subBallThrown()
{
    BaseballPlayer* pitcher = getPitcher();
    pitcher->ballThrown(-1);
    balls--;
    emit updateCount(balls, strikes, outs);
    emit pitchCountUpdate(pitcher->getName() + ": " + pitcher->getTodaysPitchCount());
}

void BaseballGame::strikeThrown()
{
    BaseballPlayer* pitcher = getPitcher();
    pitcher->strikeThrown(1);
    strikes++;
    emit updateCount(balls, strikes, outs);
    emit pitchCountUpdate(pitcher->getName() + ": " + pitcher->getTodaysPitchCount());
}

void BaseballGame::subStrikeThrown()
{
    BaseballPlayer* pitcher = getPitcher();
    pitcher->strikeThrown(-1);
    strikes--;
    emit updateCount(balls, strikes, outs);
    emit pitchCountUpdate(pitcher->getName() + ": " + pitcher->getTodaysPitchCount());
}

void BaseballGame::foulBall()
{
    BaseballPlayer* pitcher = getPitcher();
    pitcher->strikeThrown(1);
    if (strikes < 2) {
        strikes++;
        emit updateCount(balls, strikes, outs);
    }
    emit pitchCountUpdate(pitcher->getName() + ": " + pitcher->getTodaysPitchCount());
}

void BaseballGame::subFoulBall()
{
    BaseballPlayer* pitcher = getPitcher();
    pitcher->strikeThrown(-1);
    emit pitchCountUpdate(pitcher->getName() + ": " + pitcher->getTodaysPitchCount());
}

void BaseballGame::out()
{
    BaseballPlayer* pitcher = getPitcher();
    pitcher->recordOut(1);
    outs++;
    emit updateCount(balls, strikes, outs);
    checkOuts();
    emit pitchCountUpdate(pitcher->getName() + ": " + pitcher->getTodaysPitchCount());
}

void BaseballGame::subOut()
{
    BaseballPlayer* pitcher = getPitcher();
    pitcher->recordOut(-1);
    outs--;
    emit updateCount(balls, strikes, outs);
    emit pitchCountUpdate(pitcher->getName() + ": " + pitcher->getTodaysPitchCount());
}

void BaseballGame::clearCount()
{
    balls = strikes = 0;
    emit updateCount(balls, strikes, outs);
}

void BaseballGame::single()
{
    BaseballPlayer* pitcher = getPitcher();
    BaseballPlayer* batter = getBatter();

    batter->applyBaseHit(1);
    pitcher->applyHitAllowed(1);
    pitcher->strikeThrown(1);
    addHit();
    setOnFirst(true);
    advanceBatter();
    clearCount();
}

void BaseballGame::double2b()
{
    BaseballPlayer* pitcher = getPitcher();
    BaseballPlayer* batter = getBatter();

    batter->applyBaseHit(2);
    pitcher->applyHitAllowed(1);
    pitcher->strikeThrown(1);
    addHit();
    setOnSecond(true);
    advanceBatter();
    clearCount();
}

void BaseballGame::triple()
{
    BaseballPlayer* pitcher = getPitcher();
    BaseballPlayer* batter = getBatter();

    batter->applyBaseHit(3);
    pitcher->applyHitAllowed(1);
    pitcher->strikeThrown(1);
    addHit();
    setOnThird(true);
    advanceBatter();
    clearCount();
}

void BaseballGame::homeRun()
{
    BaseballPlayer* pitcher = getPitcher();
    BaseballPlayer* batter = getBatter();

    batter->applyBaseHit(4);
    pitcher->applyHitAllowed(1);

    pitcher->strikeThrown(1);
    addHit();

    int runsScored = 1;
    if (onFirst) runsScored++;
    if (onSecond) runsScored++;
    if (onThird) runsScored++;
    addScore(runsScored);
    advanceBatter();
    clearCount();
    clearBases();
}

void BaseballGame::strikeOut()
{
    strikeThrown();
    BaseballPlayer* pitcher = getPitcher();
    BaseballPlayer* batter = getBatter();
    batter->applyStrikeOutBatter();
    pitcher->applyStrikeOutPitcher();
    advanceBatter();
    clearCount();
    out();
}

void BaseballGame::walk()
{
    ballThrown();
    BaseballPlayer* pitcher = getPitcher();
    BaseballPlayer* batter = getBatter();
    pitcher->applyWalkPitcher();
    batter->applyWalk(1);
    advanceBatter();
    clearCount();
    setOnFirst(true);
}

void BaseballGame::hitByPitch()
{
    ballThrown();
    BaseballPlayer* pitcher = getPitcher();
    BaseballPlayer* batter = getBatter();
    batter->applyWalk(2);
    setOnFirst(true);
    advanceBatter();
    clearCount();
}

void BaseballGame::reachOnError()
{
    strikeThrown();
    BaseballPlayer* pitcher = getPitcher();
    BaseballPlayer* batter = getBatter();
    batter->applyGenericOut();
    addError();
    advanceBatter();
    clearCount();
}

void BaseballGame::genOut()
{
    strikeThrown();
    BaseballPlayer* pitcher = getPitcher();
    BaseballPlayer* batter = getBatter();
    batter->applyGenericOut();
    //pitcher->recordOut(1);
    advanceBatter();
    clearCount();
    out();
}

void BaseballGame::fielderChoice()
{
    strikeThrown();
    BaseballPlayer* pitcher = getPitcher();
    BaseballPlayer* batter = getBatter();
    batter->applyGenericOut();
    //pitcher->recordOut(1);
    advanceBatter();
    clearCount();
    //setOnFirst(true);
    out();
}

void BaseballGame::doublePlay()
{
    strikeThrown();
    BaseballPlayer* pitcher = getPitcher();
    BaseballPlayer* batter = getBatter();
    batter->applyGenericOut();
    //pitcher->recordOut(2);
    advanceBatter();
    clearCount();
    setOnFirst(false);
    out();
    out();
}

void BaseballGame::sacrifice()
{
    strikeThrown();
    BaseballPlayer* pitcher = getPitcher();
    //pitcher->recordOut(1);
    advanceBatter();
    clearCount();
    out();
}
bool BaseballGame::getOnThird() const
{
    return onThird;
}

void BaseballGame::setOnThird(bool value)
{
    onThird = value;
    emit thirdBaseStatus(onThird);
}

bool BaseballGame::getOnSecond() const
{
    return onSecond;
}

void BaseballGame::setOnSecond(bool value)
{
    onSecond = value;
    emit secondBaseStatus(onSecond);
}

bool BaseballGame::getOnFirst() const
{
    return onFirst;
}

void BaseballGame::setOnFirst(bool value)
{
    onFirst = value;
    emit firstBaseStatus(onFirst);
}

int BaseballGame::getOuts() const
{
    return outs;
}

void BaseballGame::setOuts(int value)
{
    outs = value;
}

QString BaseballGame::getInningText()
{
    if (period == 0) return "Starts soon";
    QString periodStr = QString::number(period);
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
    return inningMod + " " + periodStr;
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
