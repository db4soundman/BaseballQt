#ifndef AWAYTEAMINFO_H
#define AWAYTEAMINFO_H

#include <QWizardPage>
#include <QLineEdit>
#include <QSpinBox>

class AwayTeamInfo : public QWizardPage {
public:
    AwayTeamInfo(int* pkA, int* pkoppA, int* ppgA, int* ppoppA, QString* goaliesA);

    bool validatePage();

private:
    QLineEdit goaliesInput;
    QSpinBox pkInput, pkoppInput, ppgInput, ppoppInput;
    int *pkAddr, *pkoppAddr, *ppgAddr, *ppoppAddr;
    QString* goaliesAddr;
};

#endif // AWAYTEAMINFO_H
