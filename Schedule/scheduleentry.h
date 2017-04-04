#ifndef SCHEDULEENTRY_H
#define SCHEDULEENTRY_H

#include <QObject>

class ScheduleEntry
{
public:
    ScheduleEntry(QString pMonth, int pNumGames, QString pDate1, QString pva,
                  QString pOpp, QString pTime1, QString media1, QString pDate2="",
                  QString pTime2="", QString media2="");

    QString getVsAt() const;
    void setVsAt(const QString &value);

    QString getOpp() const;
    void setOpp(const QString &value);

    QString getTime1() const;
    void setTime1(const QString &value);

    QString getTime2() const;
    void setTime2(const QString &value);

    QString getMonth1() const;
    void setMonth1(const QString &value);

    QString getMonth2() const;
    void setMonth2(const QString &value);

    QString getDate1() const;
    void setDate1(const QString &value);

    QString getDate2() const;
    void setDate2(const QString &value);

    QString getMedia1() const;
    void setMedia1(const QString &value);

    QString getMedia2() const;
    void setMedia2(const QString &value);

    int getNumGames() const;
    void setNumGames(int value);

private:
    QString vsAt, opp, time1, time2, month1, month2, date1, date2, media1, media2;
    int numGames;
};

#endif // SCHEDULEENTRY_H
