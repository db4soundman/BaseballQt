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
    void requestLt(int index);
    void requestSb(int index);

private slots:
    void requestLt();
    void requestSb();
    void updateBatterLabel(QString player);

private:
    QLabel currentBatter;
    QPushButton displayLt, displayBar;
};

#endif // BATTERSTATCONTROL_H
