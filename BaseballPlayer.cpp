#include "BaseballPlayer.h"
#define WALK 1
#define HBP 2

BaseballPlayer::BaseballPlayer() {
    abToday= rToday= hToday= rbiToday= hrToday= walksToday= strikeoutsToday= hbpToday=pitchCount= ballsThrown= strikesThrown= outsToday =0;
}


QString BaseballPlayer::getName() const {
    return name;
}

void BaseballPlayer::setName(const QString& value) {
    name = value;
}
QString BaseballPlayer::getUni() const {
    return uni;
}

void BaseballPlayer::setUni(const QString& value) {
    uni = value;
}
QString BaseballPlayer::getYear() const {
    return year;
}

void BaseballPlayer::setYear(const QString& value) {
    year = value;
}
int BaseballPlayer::getGp() const
{
    return gp;
}

void BaseballPlayer::setGp(int value)
{
    gp = value;
}
int BaseballPlayer::getSacFly() const
{
    return sacFly;
}

void BaseballPlayer::setSacFly(int value)
{
    sacFly = value;
}
int BaseballPlayer::getAb() const
{
    return ab;
}

void BaseballPlayer::setAb(int value)
{
    ab = value;
}
int BaseballPlayer::getR() const
{
    return r;
}

void BaseballPlayer::setR(int value)
{
    r = value;
}
int BaseballPlayer::getH() const
{
    return h;
}

void BaseballPlayer::setH(int value)
{
    h = value;
}
int BaseballPlayer::getRbi() const
{
    return rbi;
}

void BaseballPlayer::setRbi(int value)
{
    rbi = value;
}
int BaseballPlayer::getHr() const
{
    return hr;
}

void BaseballPlayer::setHr(int value)
{
    hr = value;
}
int BaseballPlayer::getWalks() const
{
    return walks;
}

void BaseballPlayer::setWalks(int value)
{
    walks = value;
}
int BaseballPlayer::getStrikeouts() const
{
    return strikeouts;
}

void BaseballPlayer::setStrikeouts(int value)
{
    strikeouts = value;
}
int BaseballPlayer::getHbp() const
{
    return hbp;
}

void BaseballPlayer::setHbp(int value)
{
    hbp = value;
}
int BaseballPlayer::getOuts() const
{
    return outs;
}

void BaseballPlayer::setOuts(int value)
{
    outs = value;
}
int BaseballPlayer::getAp() const
{
    return ap;
}

void BaseballPlayer::setAp(int value)
{
    ap = value;
}
int BaseballPlayer::getGs() const
{
    return gs;
}

void BaseballPlayer::setGs(int value)
{
    gs = value;
}
int BaseballPlayer::getWins() const
{
    return wins;
}

void BaseballPlayer::setWins(int value)
{
    wins = value;
}
int BaseballPlayer::getLosses() const
{
    return losses;
}

void BaseballPlayer::setLosses(int value)
{
    losses = value;
}
int BaseballPlayer::getSaves() const
{
    return saves;
}

void BaseballPlayer::setSaves(int value)
{
    saves = value;
}
int BaseballPlayer::getHitsAllowed() const
{
    return hitsAllowed;
}

void BaseballPlayer::setHitsAllowed(int value)
{
    hitsAllowed = value;
}
int BaseballPlayer::getRunsAllowed() const
{
    return runsAllowed;
}

void BaseballPlayer::setRunsAllowed(int value)
{
    runsAllowed = value;
}
int BaseballPlayer::getEr() const
{
    return er;
}

void BaseballPlayer::setEr(int value)
{
    er = value;
}
int BaseballPlayer::getBb() const
{
    return bb;
}

void BaseballPlayer::setBb(int value)
{
    bb = value;
}
int BaseballPlayer::getKOut() const
{
    return kOut;
}

void BaseballPlayer::setKOut(int value)
{
    kOut = value;
}
QString BaseballPlayer::getEra() const
{
    return era;
}

void BaseballPlayer::setEra(const QString &value)
{
    era = value;
}

QString BaseballPlayer::getAvg()
{
    return QString::number(h*1.0 / ab, 'g', 3);
}

QString BaseballPlayer::getIp()
{
    return QString::number(outs/3) + "." + QString::number(outs%3);
}

QString BaseballPlayer::getIpToday()
{
    return QString::number(outsToday/3) + "." + QString::number(outsToday%3);
}
int BaseballPlayer::getAbToday() const
{
    return abToday;
}

void BaseballPlayer::setAbToday(int value)
{
    abToday = value;
}
int BaseballPlayer::getRToday() const
{
    return rToday;
}

void BaseballPlayer::setRToday(int value)
{
    rToday = value;
}
int BaseballPlayer::getHToday() const
{
    return hToday;
}

void BaseballPlayer::setHToday(int value)
{
    hToday = value;
}
int BaseballPlayer::getRbiToday() const
{
    return rbiToday;
}

void BaseballPlayer::setRbiToday(int value)
{
    rbiToday = value;
}
int BaseballPlayer::getHrToday() const
{
    return hrToday;
}

void BaseballPlayer::setHrToday(int value)
{
    hrToday = value;
}
int BaseballPlayer::getWalksToday() const
{
    return walksToday;
}

void BaseballPlayer::setWalksToday(int value)
{
    walksToday = value;
}
int BaseballPlayer::getStrikeoutsToday() const
{
    return strikeoutsToday;
}

void BaseballPlayer::setStrikeoutsToday(int value)
{
    strikeoutsToday = value;
}
int BaseballPlayer::getHbpToday() const
{
    return hbpToday;
}

void BaseballPlayer::setHbpToday(int value)
{
    hbpToday = value;
}
int BaseballPlayer::getPitchCount() const
{
    return pitchCount;
}

void BaseballPlayer::setPitchCount(int value)
{
    pitchCount = value;
}
int BaseballPlayer::getBallsThrown() const
{
    return ballsThrown;
}

void BaseballPlayer::setBallsThrown(int value)
{
    ballsThrown = value;
}
int BaseballPlayer::getStrikesThrown() const
{
    return strikesThrown;
}

void BaseballPlayer::setStrikesThrown(int value)
{
    strikesThrown = value;
}
int BaseballPlayer::getOutsToday() const
{
    return outsToday;
}

void BaseballPlayer::setOutsToday(int value)
{
    outsToday = value;
}
int BaseballPlayer::getDoubles() const
{
    return doubles;
}

void BaseballPlayer::setDoubles(int value)
{
    doubles = value;
}
int BaseballPlayer::getTriples() const
{
    return triples;
}

void BaseballPlayer::setTriples(int value)
{
    triples = value;
}

void BaseballPlayer::applyBaseHit(int base)
{
    hToday++;
    abToday++;
    switch (base) {
    case 2:
        doubles++;
        break;
    case 3:
        triples++;
        break;
    case 4:
        hr++;
        break;
    default:
        break;
    }
}

void BaseballPlayer::applyWalk(int type)
{
    if (type == WALK)
        walksToday++;
    else hbpToday++;
}

void BaseballPlayer::applySacFly()
{
    sacFly++;
}

void BaseballPlayer::applyGenericOut()
{
    abToday++;
}

void BaseballPlayer::applyStrikeOutBatter()
{
    strikeoutsToday++;
}

void BaseballPlayer::ballThrown(int value)
{
    ballsThrown += value;
    pitchCount += value;
}

void BaseballPlayer::strikeThrown(int value)
{
    strikesThrown += value;
    pitchCount += value;
}

void BaseballPlayer::recordOut(int value)
{
    outsToday += value;
}

void BaseballPlayer::applyHitAllowed(int value)
{
    hitsAllowed += value;
}
