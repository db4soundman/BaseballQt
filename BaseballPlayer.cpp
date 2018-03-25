#include "BaseballPlayer.h"
#define WALK 1
#define HBP 2

BaseballPlayer::BaseballPlayer() {
    gp=0;
    rbi =0;
    ab=0;
    hr=0;
    h=0;
    doubles=0;
    hbp=0;
    r=0;
    strikeouts = 0;
    sacFly = 0;
    triples = 0;
    walks = 0;
    abToday= 0;
    rToday= 0;
    hToday=0;
    rbiToday= 0;
    hrToday= 0;
    walksToday= 0;
    strikeoutsToday= 0;
    hbpToday=0;
    pitchCount= 0;
    ballsThrown= 0;
    strikesThrown=0;
    outsToday= 0;
    outs= 0;
    ap=0;
    gs= 0;
    wins= 0;
    losses= 0;
    saves= 0;
    hitsAllowed= 0;
    runsAllowed= 0;
    er=0;
    bb= 0;
    kOut = 0;
    pStrikeOutsToday=0;
    pWalksToday=0;
    year="";
    pos="";
    bats="";
    throws="";
    era = "0.00";
    pos = "";
    bats = "";
    throws = "";
    name = "NO NAME";
}

BaseballPlayer::BaseballPlayer(const BaseballPlayer &p)
{
    gp=p.gp;
    rbi = p.rbi;
    ab=p.ab;
    hr=p.hr;
    abToday= p.abToday;
    rToday= p.rToday;
    hToday=p.hToday;
    rbiToday= p.rbiToday;
    hrToday= p.hrToday;
    walksToday= p.walksToday;
    strikeoutsToday= p.strikeoutsToday;
    hbpToday=p.hbpToday;
    pitchCount= p.pitchCount;
    ballsThrown= p.ballsThrown;
    strikesThrown= p.strikesThrown;
    outsToday =p.outsToday;
    outs= p.outs;
    ap= p.ap;
    gs= p.gs;
    wins= p.wins;
    losses= p.losses;
    saves= p.saves;
    hitsAllowed= p.hitsAllowed;
    runsAllowed= p.runsAllowed;
    er= p.er;
    bb= p.bb;
    kOut = p.kOut;
    pStrikeOutsToday=p.pStrikeOutsToday;
    pWalksToday=p.walksToday;
    era = p.era;
    pos = p.pos;
    bats = p.bats;
    throws = p.throws;
    name=p.name;
    uni = p.uni;
    year=p.year;
    pos=p.pos;
    bats=p.bats;
    throws=p.throws;
    doubles=p.doubles;
    hbp=p.hbp;
    r=p.r;
    sacFly = p.sacFly;
    triples = p.triples;
    walks = p.walks;
    strikeouts = p.strikeouts;
    h=p.h;
}

BaseballPlayer &BaseballPlayer::operator =(const BaseballPlayer &p)
{
    gp=p.gp;
    rbi = p.rbi;
    ab=p.ab;
    hr=p.hr;
    abToday= p.abToday;
    rToday= p.rToday;
    hToday=p.hToday;
    rbiToday= p.rbiToday;
    hrToday= p.hrToday;
    walksToday= p.walksToday;
    strikeoutsToday= p.strikeoutsToday;
    hbpToday=p.hbpToday;
    pitchCount= p.pitchCount;
    ballsThrown= p.ballsThrown;
    strikesThrown= p.strikesThrown;
    outsToday =p.outsToday;
    outs= p.outs;
    ap= p.ap;
    gs= p.gs;
    wins= p.wins;
    losses= p.losses;
    saves= p.saves;
    hitsAllowed= p.hitsAllowed;
    runsAllowed= p.runsAllowed;
    er= p.er;
    bb= p.bb;
    kOut = p.kOut;
    pStrikeOutsToday=p.pStrikeOutsToday;
    pWalksToday=p.walksToday;
    era = p.era;
    pos = p.pos;
    bats = p.bats;
    throws = p.throws;
    name=p.name;
    uni = p.uni;
    year=p.year;
    pos=p.pos;
    bats=p.bats;
    throws=p.throws;
    doubles=p.doubles;
    hbp=p.hbp;
    r=p.r;
    sacFly = p.sacFly;
    triples = p.triples;
    walks = p.walks;
    strikeouts = p.strikeouts;
    h=p.h;
    return *this;
}

bool BaseballPlayer::operator ==(const BaseballPlayer &p) const
{
    return this->name==p.name;
}

bool BaseballPlayer::operator !=(const BaseballPlayer &p) const
{
    return !(*this == p);
}

bool BaseballPlayer::operator <(const BaseballPlayer &p) const
{
    return uni.toInt() < p.uni.toInt();
}


QString BaseballPlayer::getName() const {
    return name;
}

void BaseballPlayer::setName(const QString& value) {
    name = value;
}

QString BaseballPlayer::getLastName() const
{
    return name.mid(name.indexOf(" "));
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
    return rbi + rbiToday;
}

void BaseballPlayer::setRbi(int value)
{
    rbi = value;
}
int BaseballPlayer::getHr() const
{
    return hr + hrToday;
}

void BaseballPlayer::setHr(int value)
{
    hr = value;
}
int BaseballPlayer::getWalks() const
{
    return walks + walksToday;
}

void BaseballPlayer::setWalks(int value)
{
    walks = value;
}
int BaseballPlayer::getStrikeouts() const
{
    return strikeouts + strikeoutsToday;
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
    if (ab + abToday == 0) return ".000";
    QString avg = QString::number((h+hToday)*1.0 / (ab+abToday), 'f', 3);
    if (avg.contains("0.")) {
        avg = avg.mid(1);
    }
    return avg;
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
        hrToday++;
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
    applyGenericOut();
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

void BaseballPlayer::applyStrikeOutPitcher()
{
    pStrikeOutsToday++;
}

void BaseballPlayer::applyWalkPitcher()
{
    pWalksToday++;
}
int BaseballPlayer::getPStrikeOutsToday() const
{
    return pStrikeOutsToday;
}

void BaseballPlayer::setPStrikeOutsToday(int value)
{
    pStrikeOutsToday = value;
}
int BaseballPlayer::getPWalksToday() const
{
    return pWalksToday;
}

void BaseballPlayer::setPWalksToday(int value)
{
    pWalksToday = value;
}
QString BaseballPlayer::getPos() const
{
    return pos;
}

void BaseballPlayer::setPos(const QString &value)
{
    pos = value;
}

QString BaseballPlayer::getTodaysPitchCount()
{
    return QString::number(pitchCount) + " PITCHES, " + QString::number(ballsThrown) + " BALLS, "+
               QString::number(strikesThrown) + " STRIKES";
}

QString BaseballPlayer::getBats() const
{
    return bats;
}

void BaseballPlayer::setBats(const QString &value)
{
    bats = value;
}

QString BaseballPlayer::getThrows() const
{
    return throws;
}

void BaseballPlayer::setThrows(const QString &value)
{
    throws = value;
}

void BaseballPlayer::reset()
{
    abToday = rToday = hToday = rbiToday = hrToday = walksToday = strikeoutsToday = hbpToday = pitchCount = ballsThrown = strikesThrown = outsToday = pStrikeOutsToday = pWalksToday = 0;
}



