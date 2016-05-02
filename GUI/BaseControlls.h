#ifndef BASECONTROLLS_H
#define BASECONTROLLS_H

#include <QWidget>
#include <QGroupBox>
#include <QPushButton>
#include <QLabel>
#include "BaseballGame.h"

class BaseControlls : public QGroupBox
{
    Q_OBJECT
public:
    BaseControlls(BaseballGame* game);

signals:

public slots:
    void updateFirst(bool on);
    void updateSecond(bool on);
    void updateThird(bool on);
    void clearBases();


private:
    QPushButton first, second, third, clear, firstSecond, firstThird, secondThird, loaded;
    QLabel firstLabel, secondLabel, thirdLabel;
    //QLabel
};

#endif // BASECONTROLLS_H
