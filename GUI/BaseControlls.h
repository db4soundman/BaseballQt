#ifndef BASECONTROLLS_H
#define BASECONTROLLS_H

#include <QWidget>
#include <QPushButton>
#include "BaseballGame.h"

class BaseControlls : public QWidget
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

};

#endif // BASECONTROLLS_H
