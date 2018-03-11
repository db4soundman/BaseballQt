#ifndef MIAMIALLACCESSBASEBALL_H
#define MIAMIALLACCESSBASEBALL_H

#include <QApplication>
#include "BaseballGame.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include "MainWindow.h"
#include "DefenseGraphic.h"
#include "BattingOrder.h"
#include "PitcherGraphic.h"
#include <QImage>
#include "CommercialGraphic.h"
#include "Params.h"
//#include "StatCrewScanner.h"
#include "TricasterHandler.h"
#include "LineScore.h"
#include "StandingsGraphic.h"

class MiamiAllAccessBaseball : public QApplication {
public:
    MiamiAllAccessBaseball(int &argc, char *argv[]);
    ~MiamiAllAccessBaseball();

    /**
     * @brief getAppDirPath Gets the file path to the application
     * directory.
     * @return A QString representing the file path to the application
     * directory.
     */
    static QString getAppDirPath();
    static QString getEspnImagesPath();


    void checkAppDirectory();

    static QPixmap getImgFromResources(QString name, int maxHeight, int maxWidth = 1920);
    static QPixmap getImgFromESPN(QString name, int maxHeight, int maxWidth = 1920);

    int exec();
    static QImage getTrimmedLogo(QString filePath);

private:
    QGraphicsView* tv;
    QGraphicsScene* scene;
    BaseballGame* game;
    MainWindow* controlPanel;
    CommercialGraphic* commercial;
    //StatCrewScanner* stats;
    TricasterHandler* tricaster;
    PitcherGraphic* pitcherVert;
    DefenseGraphic* defense;
    BattingOrder* battingOrderGraphic;
    LineScore* lineScore;
    Params params;
    ScheduleGraphic scheduleGraphic;
    StandingsGraphic standings;


};

#endif // MIAMIALLACCESSBASEBALL_H
