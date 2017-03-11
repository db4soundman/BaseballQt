#ifndef LINEUPS_H
#define LINEUPS_H
#include <QComboBox>
#include <QGroupBox>
#include "BaseballGame.h"
class Lineups : public QGroupBox
{
    Q_OBJECT
public:
    Lineups(BaseballGame* game);

public slots:
    void awayLineupChanged();
    void homeLineupChanged();

signals:
    void homeBattingOrderUpdate(QList<int> ind, QList<QString>p);
    void awayBattingOrderUpdate(QList<int> ind, QList<QString>p);
    void homeDefenseUpdate(QList<int> ind);
    void awayDefenseUpdate(QList<int> ind);

private:
    QList<QComboBox*> awayOrder, homeOrder, awayDef, homeDef;
};

#endif // LINEUPS_H
