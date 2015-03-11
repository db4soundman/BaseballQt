#ifndef MIAMIALLACCESSBASEBALL_H
#define MIAMIALLACCESSBASEBALL_H

#include <QApplication>
#include "BaseballGame.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include "MainWindow.h"

#include "CommercialGraphic.h"

//#include "StatCrewScanner.h"
#include "TricasterHandler.h"

class MiamiAllAccessBaseball : public QApplication {
public:
    MiamiAllAccessBaseball(int &argc, char *argv[]);

    /**
     * @brief getAppDirPath Gets the file path to the application
     * directory.
     * @return A QString representing the file path to the application
     * directory.
     */
    static QString getAppDirPath();


    void checkAppDirectory();

    int exec();

private:
    QGraphicsView* tv;
    QGraphicsScene* scene;
    BaseballGame* game;
    MainWindow* controlPanel;
    CommercialGraphic* commercial;
    //StatCrewScanner* stats;
    TricasterHandler* tricaster;
};

#endif // MIAMIALLACCESSBASEBALL_H
