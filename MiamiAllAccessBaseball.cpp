#include "MiamiAllAccessBaseball.h"
#include <QStandardPaths>
#include <QDir>
#include <QFile>
#include "SetupWizard.h"
#include <QDesktopWidget>
#include <QAction>

MiamiAllAccessBaseball::MiamiAllAccessBaseball(int& argc, char* argv[]) :
    QApplication (argc, argv) {
    setApplicationName("Miami All-Access Baseball");
}

QString
MiamiAllAccessBaseball::getAppDirPath() {
    return QStandardPaths::writableLocation(QStandardPaths::DataLocation);
}

void
MiamiAllAccessBaseball::checkAppDirectory() {
    QDir appDir(QStandardPaths::writableLocation(QStandardPaths::DataLocation));
    if (!appDir.exists()) {
        appDir.mkdir(QStandardPaths::writableLocation(QStandardPaths::DataLocation));
    }
}

int
MiamiAllAccessBaseball::exec() {
    //checkAppDirectory();

    // Make vars, create wizard.
    scene = new QGraphicsScene();

    QString awayName, homeName, awayRank, homeRank, homeFile, awayFile, sponsor, announcer,
            awayLogo;
    QColor awayColor, homeColor,  bg;
    int pk, pkopp, ppg, ppopp;
    bool usingTricaster = true;
    homeColor.setRgb(226, 24, 54);
    bg.setRgb(0,120,0);
    announcer = "Randy Hollowell";
    sponsor = "Miami IMG Sports Network";
    homeName = "MIAMI";
    QDesktopWidget desktop;

    SetupWizard wizard(&awayName, &homeName, &awayFile, &homeFile, &sponsor,
                       &announcer, &awayRank, &homeRank, &awayColor, &homeColor,
                       &bg, &usingTricaster, &awayLogo);
    wizard.exec();
    QRect graphicsScreen = usingTricaster ? QRect(0,0,1920,1080) : desktop.screenGeometry(0);
    game = new BaseballGame(awayName, homeName, awayColor, homeColor,
                          awayFile, homeFile, sponsor, announcer, awayRank,
                          homeRank, graphicsScreen.width() + 1, awayLogo);
    if (usingTricaster)
        bg.setRgb(0,0,0);

    pitcherVert = new PitcherGraphic(game);
    defense = new DefenseGraphic(game);
    battingOrderGraphic = new BattingOrder(game);
    connect(game, SIGNAL(showDefense(bool)), defense, SLOT(displayGraphic(bool)));
    connect(game, SIGNAL(showBatters(bool)), battingOrderGraphic, SLOT(displayGraphic(bool)));
    scene->addItem(game->getSb());

    scene->addItem(game->getLt());
    commercial = new CommercialGraphic(game, graphicsScreen.width(), awayLogo);
    scene->addItem(commercial);
    game->getLt()->setX((graphicsScreen.width() / 2) - 214);
    game->getLt()->setY(graphicsScreen.height() - 160);
    game->getSb()->setY(80);
    game->getSb()->setX((graphicsScreen.width() / 2) - (game->getSb()->getRealWidth()/2));
    commercial->setY(graphicsScreen.height() - 230);
    tv = new QGraphicsView(scene);



    tv->setGeometry(graphicsScreen);
    tv->setSceneRect(0, 0,graphicsScreen.width(), graphicsScreen.height());
    tv->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tv->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tv->setBackgroundBrush(bg);
    tv->setFrameShape(QFrame::NoFrame);

    controlPanel = new MainWindow(game, commercial, pitcherVert, defense, battingOrderGraphic);
    controlPanel->show();
    if (!usingTricaster)
        tv->showFullScreen();
    else {
        tricaster = new TricasterHandler(tv, bg);
        game->getSb()->setUseTransparency(true);
        connect(scene, SIGNAL(changed(QList<QRectF>)), tricaster, SLOT(updatePortion(QList<QRectF>)));
        connect(game->getSb(), SIGNAL(transparentField(int,int,int,int)), tricaster, SLOT(addAlphaRect(int,int,int,int)));
        connect(game->getSb(), SIGNAL(removeTransparentField(int,int,int,int)), tricaster, SLOT(removeAlphaRect(int,int,int,int)));
    }
    return QApplication::exec();
}


