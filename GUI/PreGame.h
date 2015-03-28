#ifndef PREGAME_H
#define PREGAME_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include "BaseballGame.h"

class PreGame : public QWidget
{
    Q_OBJECT
public:
    PreGame(BaseballGame* game);


signals:

public slots:

private:
    QPushButton battingOrder, defenseGraphic;
};

#endif // PREGAME_H
