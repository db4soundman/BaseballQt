#ifndef BATTERSTATCONTROL_H
#define BATTERSTATCONTROL_H

#include <QWidget>
#include "BaseballGame.h"
#include <QLabel>
#include <QPushButton>

class BatterStatControl : public QWidget {
    Q_OBJECT
public:
    BatterStatControl(BaseballGame* game);

signals:


private slots:
    void updateBatterLabel(QString player);

private:
    QLabel currentBatter;
    QPushButton displayLt, displayBar;
};

#endif // BATTERSTATCONTROL_H
