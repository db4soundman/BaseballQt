#include "AwayTeamInfo.h"
#include <QFormLayout>
#include <QLabel>

AwayTeamInfo::AwayTeamInfo(int* pkA, int* pkoppA, int* ppgA, int* ppoppA, QString* goaliesA) {
    setTitle("Visiting Team Information");
    pkAddr = pkA;
    pkoppAddr = pkoppA;
    ppgAddr = ppgA;
    ppoppAddr = ppoppA;
    goaliesAddr = goaliesA;
    pkInput.setMaximum(1000);
    pkoppInput.setMaximum(1000);
    ppgInput.setMaximum(1000);
    ppoppInput.setMaximum(1000);
    QFormLayout* mainLayout = new QFormLayout();
    mainLayout->addRow(new QLabel("Pk"), &pkInput);
    mainLayout->addRow("Pk Opp", &pkoppInput);
    mainLayout->addRow("PP Goals", &ppgInput);
    mainLayout->addRow("PP Opp", &ppoppInput);
    mainLayout->addRow("Goalies (separate by space)", &goaliesInput);

    setLayout(mainLayout);
}

bool AwayTeamInfo::validatePage()
{
    *pkAddr = pkInput.value();
    *pkoppAddr = pkoppInput.value();
    *ppgAddr = ppgInput.value();
    *ppoppAddr = ppoppInput.value();
    *goaliesAddr = goaliesInput.text();
    return true;
}
