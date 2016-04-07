#ifndef SETUPPAGE_H
#define SETUPPAGE_H

#include <QWizardPage>
#include <QPushButton>
#include <QColor>
#include <QLineEdit>
#include <QCheckBox>
#include <QPixmap>
#include <QLabel>
#include <QComboBox>
#include "Profile.h"

class SetupPage : public QWizardPage {
    Q_OBJECT
public:
    SetupPage(QString* pAwayName, QString* pHomeName, QString* pAwayFile, QString* pHomeFile,
              QString* pSponsor, QString* pAnnouncer, QString* pAwayRank, QString* pHomeRank,
              QColor* pAwayColor, QColor* pHomeColor, QColor* pBg, bool *pUsingTricaster,
              QString *pawayLogo, QString *tricasterIp, QString *aSname, QString *hSname, int* portNum);
    bool validatePage();

private slots:
    void homeBrowse();
    void awayBrowse();
    void profileBrowse();
    void awayColorDiag();
    void homeColorDiag();
    void bgDiag();
    void logoBrowse();
    void applyProfile();

private:
    QString* awayName, *homeName, *awayRank, *homeRank, *homeFile, *awayFile, *sponsor, *announcer, *awayLogo, *tricasterIp, *awayShort, *homeShort;
    QColor* awayColor, *homeColor,  *bg;
    QPushButton browseAway, browseHome, chooseHColor, chooseAColor, chooseBg, browseStatCrew, browseLogo, profileDialog;
    QLineEdit homeNameLine, awayNameLine, awayRankLine, homeRankLine, sponsorLine, announcerLine, tricasterIpLine, awayShortLine, homeShortLine;
    QCheckBox* tricasterBox;
    QPixmap homeColorPrev, awayColorPrev;
    QComboBox* portSelector, *swatchSelector;
    QLabel *homeColorBox, *awayColorBox;
    bool* usingTricaster;
    int *port;
    Profile activeProfile;
};

#endif // SETUPPAGE_H
