#include "MiamiAllAccessBaseball.h"
#include <QStandardPaths>
#include <QDir>
#include <QFile>
#include "SetupWizard.h"
#include <QDesktopWidget>
#include <QAction>
#include <QRect>

MiamiAllAccessBaseball::MiamiAllAccessBaseball(int& argc, char* argv[]) :
    QApplication (argc, argv) {
    setApplicationName("Miami Baseball");
}

QString
MiamiAllAccessBaseball::getAppDirPath() {
    return QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/"+(applicationName().replace(" ",""));
}

void
MiamiAllAccessBaseball::checkAppDirectory() {
    QDir appDir(getAppDirPath());
    if (!appDir.exists()) {
        appDir.mkpath(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation));
        QFile settings(":/settings");
        settings.copy(appDir.absolutePath()+"/settings.txt");
    }
    params = Params((QString("settings.txt")).toStdString());
}

int
MiamiAllAccessBaseball::exec() {
    checkAppDirectory();

    // Make vars, create wizard.
    scene = new QGraphicsScene();

    QString awayName, homeName, awayRank, homeRank, homeFile, awayFile, sponsor, announcer,
            awayLogo, tricasterIp, awayShort, homeShort;
    QColor awayColor, homeColor,  bg;
    int port;
    bool usingTricaster = true;
    homeColor.setRgb(226, 24, 54);
    bg.setRgb(0,120,0);
    announcer = QString::fromStdString(params.stringValue("ANNOUNCER"));
    sponsor = QString::fromStdString(params.stringValue("SPONSOR"));
    homeName = "MIAMI";
    homeShort = "MIAMI";
    tricasterIp = QString::fromStdString(params.stringValue("IP"));
    QDesktopWidget desktop;

    SetupWizard wizard(&awayName, &homeName, &awayFile, &homeFile, &sponsor,
                       &announcer, &awayRank, &homeRank, &awayColor, &homeColor,
                       &bg, &usingTricaster, &awayLogo, &tricasterIp, &awayShort, &homeShort, &port);
    wizard.exec();
    QRect graphicsScreen = usingTricaster ? QRect(0,0,1920,1080) : desktop.screenGeometry(1);
    QImage img = getTrimmedAwayLogo(awayLogo);
    QPixmap awayImg = QPixmap::fromImage(img);
    game = new BaseballGame(awayName, homeName, awayColor, homeColor,
                          awayFile, homeFile, sponsor, announcer, awayRank,
                          homeRank, graphicsScreen.width() + 1, awayImg);
    if (usingTricaster)
        bg.setRgb(0,0,0);

    pitcherVert = new PitcherGraphic(game);
    defense = new DefenseGraphic(game);
    battingOrderGraphic = new BattingOrder(game);
    connect(game, SIGNAL(showDefense(bool)), defense, SLOT(displayGraphic(bool)));
    connect(game, SIGNAL(showBatters(bool)), battingOrderGraphic, SLOT(displayGraphic(bool)));
    scene->addItem(game->getSb());

    scene->addItem(game->getLt());
    commercial = new CommercialGraphic(game, graphicsScreen.width(), awayImg);
    commercial->setMaaText(QString::fromStdString(params.stringValue("COMMERCIAL_TITLE")));
    scene->addItem(commercial);
    game->getLt()->setX(0);
    game->getLt()->setY(graphicsScreen.height() - 150);
    game->getSb()->setY(graphicsScreen.height() - 100);
    game->getSb()->setX(0);
    game->getSb()->setUseTransparency(usingTricaster);
    commercial->setY(graphicsScreen.height() - 350);
    tv = new QGraphicsView(scene);
    scene->addItem(defense);
    scene->addItem(pitcherVert);
    scene->addItem(battingOrderGraphic);

    defense->setX(1278 / 4);
    defense->setY(810/4);
    battingOrderGraphic->setX(1278/4);
    battingOrderGraphic->setY(810/4);
    pitcherVert->setX(1920 * 3 /4);\
    pitcherVert->setY(1080 / 2 - 388/2);

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
        tricaster = new TricasterHandler(tricasterIp, port, tv, bg);
        connect(scene, SIGNAL(changed(QList<QRectF>)), tricaster, SLOT(updatePortion(QList<QRectF>)));
        connect(game->getSb(), SIGNAL(transparentField(int,int,int,int)), tricaster, SLOT(addAlphaRect(int,int,int,int)));
        connect(game->getSb(), SIGNAL(removeTransparentField(int,int,int,int)), tricaster, SLOT(removeAlphaRect(int,int,int,int)));
    }
    return QApplication::exec();
}

QImage MiamiAllAccessBaseball::getTrimmedAwayLogo(QString filePath)
{
    int tX, tY, bX, bY;
    tX = (tY = (bX = (bY = -1)));
    QImage src(filePath);
    QColor background = src.pixel(0,0);

    // Find top most pixel
    for (int i = 0; i < src.height() / 2 && tY == -1; i++) {
        for (int j = 0; j < src.width(); j++) {
            if (QColor(src.pixel(j, i)) != background) {
                tY = i;
                break;
            }
        }
    }

    // Find bottom most pixel
    for (int i = src.height() - 1; i > src.height() / 2 && bY == -1; i--) {
        for (int j = 0; j < src.width(); j++) {
            if (QColor(src.pixel(j, i)) != background) {
                bY = i;
                break;
            }
        }
    }

    // Find left most pixel
    for (int i = 0; i < src.width()/2 && tX == -1; i++) {
        for (int j = 0; j < src.height(); j++) {
            if (QColor(src.pixel(i, j)) != background) {
                tX = i;
                break;
            }
        }
    }

    // Find the right most pixel
    for (int i = src.width() - 1; i > src.width()/2 && bX == -1; i--) {
        for (int j = 0; j < src.height(); j++) {
            if (QColor(src.pixel(i, j)) != background) {
                bX = i;
                break;
            }
        }
    }
    QPoint tl(tX, tY);
    QPoint br(bX, bY);
    QRect box(tl, br);
    return src.copy(box);
}


