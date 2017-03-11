#ifndef COUNTCONTROL_H
#define COUNTCONTROL_H

#include <QGroupBox>
#include "BaseballGame.h"
#include <QPushButton>
#include <QLabel>

class CountControl : public QGroupBox {
    Q_OBJECT
public:
    CountControl(BaseballGame* game);

signals:
    void showSOG(QString sog);

public slots:

private:


    QPushButton ballThrown, ballSub, strikeThrown, strikeSub, foul, foulSub, outPlus, outSub;


};

#endif // COUNTCONTROL_H
