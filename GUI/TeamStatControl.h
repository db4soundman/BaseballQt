#ifndef TEAMSTATCONTROL_H
#define TEAMSTATCONTROL_H

#include <QWidget>
#include "BaseballGame.h"
#include <QComboBox>
#include <QPushButton>

class TeamStatControl : public QWidget {
    Q_OBJECT
public:
    TeamStatControl(BaseballGame* game, bool home);

signals:
    void requestSeasonLt(int index);
    void requestSeasonSb(int index);
    void requestGameSb(int index);
    void requestGameLt(int index);

private slots:
    void requestSeasonLt();
    void requestGameLt();
    void requestGameSb();
    void requestSeasonSb();

private:
    QComboBox playerSelector;
    QPushButton seasonLt, gameLt, seasonBar, gameBar;
};

#endif // TEAMSTATCONTROL_H
