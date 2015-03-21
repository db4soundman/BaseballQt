#ifndef LINEUPS_H
#define LINEUPS_H
#include <QComboBox>
#include "BaseballGame.h"
class Lineups : public QWidget
{
    Q_OBJECT
public:
    Lineups(BaseballGame* game);

public slots:

signals:

private:
    QList<QComboBox*> awayOrder, homeOrder, awayDef, homeDef;
};

#endif // LINEUPS_H
