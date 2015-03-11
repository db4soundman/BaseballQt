#ifndef BASEBALLGAME_H
#define BASEBALLGAME_H

#include <QObject>
#include "Clock.h"
#include <QString>
#include <QTimer>
#include "Scoreboard.h"
#include "LowerThird.h"
#include "BaseballTeam.h"


class BaseballGame : public QObject {
    Q_OBJECT
public:
    BaseballGame(QString awayName, QString homeName, QColor awayColor, QColor homeColor,
               QString awayXML, QString homeXML, QString sponsor, QString announcers,
               QString awayRank, QString homeRank, int screenWidth, QString awayLogo);

    Scoreboard* getSb();
    LowerThird* getLt();

    QString getSponsor() const;
    void setSponsor(const QString& value);

    QString getAnnouncers() const;
    void setAnnouncers(const QString& value);

    QString getHomeName() const;
    void setHomeName(const QString& value);

    QString getAwayName() const;
    void setAwayName(const QString& value);

    BaseballTeam* getHomeTeam() const;

    BaseballTeam* getAwayTeam() const;

    Clock* getGameClock();

    QString getHomeRank() const;
    void setHomeRank(const QString& value);

    QString getAwayRank() const;
    void setAwayRank(const QString& value);

    QColor getHomeColor() const;
    void setHomeColor(const QColor& value);

    QColor getAwayColor() const;
    void setAwayColor(const QColor& value);

    int getAwayScore() const;
    void setAwayScore(int value);

    int getHomeScore() const;
    void setHomeScore(int value);

    int getPeriod() const;
    void setPeriod(int value);

    bool getIsFinal() const;
    void setIsFinal(bool value);

    int getHomeHits() const;
    void setHomeHits(int value);

    int getAwayHits() const;
    void setAwayHits(int value);

    int getHomeErrors() const;
    void setHomeErrors(int value);

    int getAwayErrors() const;
    void setAwayErrors(int value);

    int getHomeBatter() const;
    void setHomeBatter(int value);

    int getAwayBatter() const;
    void setAwayBatter(int value);

    int getStrikes() const;
    void setStrikes(int value);

    int getBalls() const;
    void setBalls(int value);

    int getOuts() const;
    void setOuts(int value);

public slots:
    void advancePeriod();
    void rewindPeriod();
    //void toggleClock();
    void homeScored(int score);
    void awayScored(int score);
    void subRunHome();
    void subRunAway();
    void addHomeHit();
    void addAwayHit();
    void subHomeHit();
    void subAwayHit();
    void showAnnouncers();
    void gatherHomeSeasonStatsLt(int index);
    void gatherHomeSeasonStatsSb(int index);
    void gatherHomeGameStatsLt(int index);
    void gatherHomeGameStatsSb(int index);
    void gatherAwaySeasonStatsLt(int index);
    void gatherAwaySeasonStatsSb(int index);
    void gatherAwayGameStatsLt(int index);
    void gatherAwayGameStatsSb(int index);
    void makeFinal();

signals:
    void homeScoreChanged(int score);
    void awayScoreChanged(int score);
    void periodChanged(QString mod, int pd);
    //void clockIsRunning(bool isRunning);
    void awayHitsChanged(int sog);
    void homeHitsChanged(int sog);
    void homeErrorsChanged(int errors);
    void awayErrorsChanged(int errors);
    void ballsChanged(int b);
    void strikesChanged(int s);
    void outsChanged(int o);

private:
    QString homeName, awayName, sponsor, announcers, homeRank,
    awayRank, inningMod;
    int awayScore, homeScore, period, homeHits, awayHits, homeErrors, awayErrors,
    homeBatter, awayBatter, strikes, balls, outs;
    //Clock gameClock;
    bool isFinal;
    QColor homeColor, awayColor;
    BaseballTeam* homeTeam;
    BaseballTeam* awayTeam;
    Scoreboard sb;
    LowerThird lt;
    // GUI is separate class
    // GraphicsVars
};

#endif // BASEBALLGAME_H
