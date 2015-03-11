#ifndef STATCREWSCANNER_H
#define STATCREWSCANNER_H

#include <QObject>
#include <QTimer>
#include "GameXmlUpdater.h"
#include "BaseballGame.h"
class StatCrewScanner : public QObject
{
    Q_OBJECT
public:
    StatCrewScanner(BaseballGame* game, QString fileName);

public slots:
    void toggleScanner(int pd);
    void toggleScanner();

private slots:
    void updateStats();

private:
    GameXmlUpdater* statCrew;
    QTimer* trigger;
    bool isActive;
    QString statFile;
};

#endif // STATCREWSCANNER_H
