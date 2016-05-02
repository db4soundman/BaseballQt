#ifndef ATBATRESULTS_H
#define ATBATRESULTS_H

#include <QWidget>
#include <QGroupBox>
#include "BaseballGame.h"
#include <QPushButton>
#include <QLabel>

class AtBatResults : public QGroupBox {
    Q_OBJECT
public:
    AtBatResults(BaseballGame* game);

signals:


private slots:


private:
    QPushButton single, double2b, triple, homeRun, walk, hbp,
    strikeout, reachedOnError, fieldersChoice, genOut, sacrifice,
    doublePlay;
};

#endif // ATBATRESULTS_H
