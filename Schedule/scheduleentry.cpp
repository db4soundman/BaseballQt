#include "scheduleentry.h"

ScheduleEntry::ScheduleEntry(QString pMonth, int pNumGames, QString pDate1,
                             QString pva, QString pOpp, QString pTime1,
                             QString media1, QString pDate2,
                             QString pTime2, QString media2) :
    numGames(pNumGames), date1(pDate1), vsAt(pva), opp(pOpp), time1(pTime1),
    media1(media1), date2(pDate2), time2(pTime2), media2(media2)
{
    month1 = pMonth.contains("/") ? pMonth.split("/")[0] : pMonth;
    month2 = pMonth.contains("/") ? pMonth.split("/")[1] : "";
}

QString ScheduleEntry::getVsAt() const
{
    return vsAt;
}

void ScheduleEntry::setVsAt(const QString &value)
{
    vsAt = value;
}

QString ScheduleEntry::getOpp() const
{
    return opp;
}

void ScheduleEntry::setOpp(const QString &value)
{
    opp = value;
}

QString ScheduleEntry::getTime1() const
{
    return time1;
}

void ScheduleEntry::setTime1(const QString &value)
{
    time1 = value;
}

QString ScheduleEntry::getTime2() const
{
    return time2;
}

void ScheduleEntry::setTime2(const QString &value)
{
    time2 = value;
}

QString ScheduleEntry::getMonth1() const
{
    return month1;
}

void ScheduleEntry::setMonth1(const QString &value)
{
    month1 = value;
}

QString ScheduleEntry::getMonth2() const
{
    return month2;
}

void ScheduleEntry::setMonth2(const QString &value)
{
    month2 = value;
}

QString ScheduleEntry::getDate1() const
{
    return date1;
}

void ScheduleEntry::setDate1(const QString &value)
{
    date1 = value;
}

QString ScheduleEntry::getDate2() const
{
    return date2;
}

void ScheduleEntry::setDate2(const QString &value)
{
    date2 = value;
}

QString ScheduleEntry::getMedia1() const
{
    return media1;
}

void ScheduleEntry::setMedia1(const QString &value)
{
    media1 = value;
}

QString ScheduleEntry::getMedia2() const
{
    return media2;
}

void ScheduleEntry::setMedia2(const QString &value)
{
    media2 = value;
}

int ScheduleEntry::getNumGames() const
{
    return numGames;
}

void ScheduleEntry::setNumGames(int value)
{
    numGames = value;
}
