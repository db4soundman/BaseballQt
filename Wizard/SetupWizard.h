#ifndef SETUPWIZARD_H
#define SETUPWIZARD_H

#include <QWizard>
#include <QPushButton>
#include <QColor>
#include "SetupPage.h"
#include "AwayTeamInfo.h"
#include "School.h"

class SetupWizard : public QWizard {
public:
    SetupWizard(QString* pAwayFile, QString* pHomeFile,
                QString* pSponsor, QString* pAnnouncer, QString* pAwayRank, QString* pHomeRank, QColor* pBg, bool* usingTricaster, QString *tricasterIp, int *port);

private:
    SetupPage wizpage;
};

#endif // SETUPWIZARD_H
