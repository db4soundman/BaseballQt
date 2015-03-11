#ifndef SETUPPAGE_H
#define SETUPPAGE_H

#include <QWizardPage>
#include <QPushButton>
#include <QColor>
#include <QLineEdit>
#include <QCheckBox>

class SetupPage : public QWizardPage {
    Q_OBJECT
public:
    SetupPage(QString* pAwayName, QString* pHomeName, QString* pAwayFile, QString* pHomeFile,
              QString* pSponsor, QString* pAnnouncer, QString* pAwayRank, QString* pHomeRank,
              QColor* pAwayColor, QColor* pHomeColor, QColor* pBg, bool *pUsingTricaster, QString *pawayLogo);
    bool validatePage();

private slots:
    void homeBrowse();
    void awayBrowse();
    void awayColorDiag();
    void homeColorDiag();
    void bgDiag();
    void logoBrowse();

private:
    QString* awayName, *homeName, *awayRank, *homeRank, *homeFile, *awayFile, *sponsor, *announcer, *awayLogo;
    QColor* awayColor, *homeColor,  *bg;
    QPushButton browseAway, browseHome, chooseHColor, chooseAColor, chooseBg, browseLogo;
    QLineEdit homeNameLine, awayNameLine, awayRankLine, homeRankLine, sponsorLine, announcerLine;
    QCheckBox* tricasterBox;
    bool* usingTricaster;
};

#endif // SETUPPAGE_H
