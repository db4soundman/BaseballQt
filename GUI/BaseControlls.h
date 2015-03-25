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

private:
    QPushButton first, second, third, clear;

};

#endif // BASECONTROLLS_H
