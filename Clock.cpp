#include "Clock.h"
#include <QTime>

Clock::Clock() {
    minutes = 20;
    regulationLength = 20;
    otLength = 5;
    seconds = 0;
    tenths = 1;
    gameClock = true;
}

Clock::Clock(int minutes) {
    this->minutes = minutes;
    seconds = 0;
    tenths = 9;
    gameClock = false;
}

void
Clock::setClock(int m, int s, int t) {
    minutes = m;
    seconds = s;
    tenths = t;
    emit clockUpdated();
    if (minutes == 0 && seconds == 0 && tenths == 0)
        emit clockExpired();
}

int
Clock::getTimeLeft() {
    return minutes*600 + seconds*10 + tenths;
}

QString
Clock::toString() {
    QTime clock(0, minutes, seconds, tenths);
    if (minutes > 0)
        return clock.toString("m:ss");
    else
        return clock.toString("s.z");
}

QString
Clock::toStringPP() {
    QTime clock(0, minutes, seconds, tenths);
    return clock.toString("m:ss");
}

QString Clock::getTimeSincePdStarted()
{
    QTime clock(0, minutes, seconds);
    QTime pd(0, 20);
    QTime retVal(0,0);
    retVal = retVal.addSecs(clock.secsTo(pd));
    return retVal.toString("m:ss");
}

QString Clock::getTimeSinceOtStarted()
{
    QTime clock(0, minutes, seconds);
    QTime pd(0, 5);
    QTime retVal(0,0);
    retVal.addSecs(clock.secsTo(pd));
    return retVal.toString("m:ss");
}

void
Clock::tick() {
    tenths --;
    if (tenths < 0) {
        tenths = 9;
        seconds --;
    }
    if (seconds < 0 && minutes > 0) {
        seconds = 59;
        minutes --;
    }

    if (minutes == 0 && seconds == 0 && tenths == 0) {
        emit clockExpired();
    }
    if (gameClock)
        emit clockUpdated();
}

void
Clock::resetClock(bool ot) {
    if (!ot) {
        setClock(regulationLength, 0, 1);
    }
    else {
        setClock(otLength, 0, 1);
    }
}
int Clock::getTenths() const
{
    return tenths;
}

void Clock::setTenths(int value)
{
    tenths = value;
}

int Clock::getSeconds() const
{
    return seconds;
}

void Clock::setSeconds(int value)
{
    seconds = value;
}

int Clock::getMinutes() const
{
    return minutes;
}

void Clock::setMinutes(int value)
{
    minutes = value;
}

bool Clock::isGameClock() const
{
    return gameClock;
}

void Clock::setGameClock(bool value)
{
    gameClock = value;
}

