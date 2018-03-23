#include "SetupWizard.h"

SetupWizard::SetupWizard(QString* pAwayFile,
                         QString* pHomeFile, QString* pSponsor, QString* pAnnouncer,
                         QString* pAwayRank, QString* pHomeRank,
                         QColor* pBg, bool *usingTricaster, QString* tricasterIp,
                         int* port) :
    wizpage(pAwayFile, pHomeFile, pSponsor, pAnnouncer,
            pAwayRank, pHomeRank, pBg,
            usingTricaster, tricasterIp, port){
    addPage(&wizpage);
}
