#ifndef BASEBALLPLAYER_H
#define BASEBALLPLAYER_H

#include <QObject>

class BaseballPlayer : public QObject {
    Q_OBJECT
public:
    BaseballPlayer();
    //BaseballPlayer& operator = (const BaseballPlayer&);

    QString getName() const;
    void setName(const QString& value);

    QString getLastName() const;

    QString getUni() const;
    void setUni(const QString& value);

    QString getYear() const;
    void setYear(const QString& value);


    int getGp() const;
    void setGp(int value);

    int getSacFly() const;
    void setSacFly(int value);

    int getAb() const;
    void setAb(int value);

    int getR() const;
    void setR(int value);

    int getH() const;
    void setH(int value);

    int getRbi() const;
    void setRbi(int value);

    int getHr() const;
    void setHr(int value);

    int getWalks() const;
    void setWalks(int value);

    int getStrikeouts() const;
    void setStrikeouts(int value);

    int getHbp() const;
    void setHbp(int value);

    int getOuts() const;
    void setOuts(int value);

    int getAp() const;
    void setAp(int value);

    int getGs() const;
    void setGs(int value);

    int getWins() const;
    void setWins(int value);

    int getLosses() const;
    void setLosses(int value);

    int getSaves() const;
    void setSaves(int value);

    int getHitsAllowed() const;
    void setHitsAllowed(int value);

    int getRunsAllowed() const;
    void setRunsAllowed(int value);

    int getEr() const;
    void setEr(int value);

    int getBb() const;
    void setBb(int value);

    int getKOut() const;
    void setKOut(int value);

    QString getEra() const;
    void setEra(const QString &value);

    QString getAvg();
    QString getIp();
    QString getIpToday();

    int getAbToday() const;
    void setAbToday(int value);

    int getRToday() const;
    void setRToday(int value);

    int getHToday() const;
    void setHToday(int value);

    int getRbiToday() const;
    void setRbiToday(int value);

    int getHrToday() const;
    void setHrToday(int value);

    int getWalksToday() const;
    void setWalksToday(int value);

    int getStrikeoutsToday() const;
    void setStrikeoutsToday(int value);

    int getHbpToday() const;
    void setHbpToday(int value);

    int getPitchCount() const;
    void setPitchCount(int value);

    int getBallsThrown() const;
    void setBallsThrown(int value);

    int getStrikesThrown() const;
    void setStrikesThrown(int value);

    int getOutsToday() const;
    void setOutsToday(int value);

    int getDoubles() const;
    void setDoubles(int value);

    int getTriples() const;
    void setTriples(int value);

    void applyBaseHit(int base);
    void applyWalk(int type);
    void applySacFly();
    void applyGenericOut();
    void applyStrikeOutBatter();

    void ballThrown(int value);
    void strikeThrown(int value);
    void recordOut(int value);
    void applyHitAllowed(int value);
    void applyStrikeOutPitcher();
    void applyWalkPitcher();


    int getPStrikeOutsToday() const;
    void setPStrikeOutsToday(int value);

    int getPWalksToday() const;
    void setPWalksToday(int value);

    QString getPos() const;
    void setPos(const QString &value);

    QString getTodaysPitchCount();

private:
    QString name, uni, year, pos;
    // Batting
    int gp, sacFly, ab, r, h, rbi, hr, walks, strikeouts, doubles, triples,
    hbp, abToday, rToday, hToday, rbiToday, hrToday, walksToday, strikeoutsToday, hbpToday;
    // Pitching
    int outs, ap, gs, wins, losses, saves, hitsAllowed, runsAllowed,
    er, bb, kOut, pitchCount, ballsThrown, strikesThrown, outsToday, pStrikeOutsToday, pWalksToday;
    QString era;
};

#endif // BASEBALLPLAYER_H
