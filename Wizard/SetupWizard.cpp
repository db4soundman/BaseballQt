#include "SetupWizard.h"

SetupWizard::SetupWizard(School *awaySchool, School *homeSchool, QString* pAwayFile,
                         QString* pHomeFile, QString* pSponsor, QString* pAnnouncer,
                         QString* pAwayRank, QString* pHomeRank,
                         QColor* pBg, bool *usingTricaster, QString* tricasterIp,
                         int* port) :
    wizpage(awaySchool, homeSchool,pAwayFile, pHomeFile, pSponsor, pAnnouncer,
            pAwayRank, pHomeRank, pBg,
            usingTricaster, tricasterIp, port){
    addPage(&wizpage);
}
