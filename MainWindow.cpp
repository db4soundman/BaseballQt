#include "MainWindow.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include "MiamiAllAccessBaseball.h"

MainWindow::MainWindow(BaseballGame* game, CommercialGraphic* comGraphic, PitcherGraphic *pg, DefenseGraphic *dg, BattingOrder *bog, LineScore *lineScore, StandingsGraphic *sg)
    : panel(game, comGraphic,pg, dg, bog, lineScore),
    awayPlayerEdit(game, false), homePlayerEdit(game, true), awayEdit(game->getAwayTeam()), homeEdit(game->getHomeTeam()),
    ltCreator(game->getLt()), standings(sg) {
    setCentralWidget(&panel);
    //setMaximumWidth(800);
    makeMenu(game);

}

MainWindow::~MainWindow() {

}

void MainWindow::attachScheduleGraphic(ScheduleGraphic *pSched)
{
    connect(&scheduleGui, SIGNAL(show(QList<ScheduleEntry>,bool)), pSched, SLOT(receiveData(QList<ScheduleEntry>,bool)));
    connect(&scheduleGui, SIGNAL(show(QList<ScheduleEntry>,bool)), pSched, SLOT(showGraphic()));
    panel.getDispControls()->addGraphicToHide(pSched);
}

void MainWindow::makeMenu(BaseballGame* game)
{
    QMenu* nchcMenu = new QMenu("MAC");
    QAction* standingsAction = new QAction(QIcon(MiamiAllAccessBaseball::getImgFromResources(":/images/MAC.png", 16)), "Edit Standings", NULL);
    nchcMenu->addAction(standingsAction);
    connect(standingsAction, SIGNAL(triggered()), &standings, SLOT(show()));

    QMenu* awayMenu = new QMenu(MiamiAllAccessBaseball::awaySchool.getTitle());
    QAction* awayPlayerEditor = new QAction("Edit Player Stats", this);
    connect(awayPlayerEditor, SIGNAL(triggered()), &awayPlayerEdit, SLOT(updateSpinBoxes()));
    connect(awayPlayerEditor, SIGNAL(triggered()), &awayPlayerEdit, SLOT(show()));
    awayMenu->addAction(awayPlayerEditor);
    QAction* awayTeamEdit = new QAction("Edit Team Stats", this);
    connect(awayTeamEdit, SIGNAL(triggered()), &awayEdit, SLOT(updateSpinBoxes()));
    connect(awayTeamEdit, SIGNAL(triggered()), &awayEdit, SLOT(show()));
    awayMenu->addAction(awayTeamEdit);

    QMenu* homeMenu = new QMenu(MiamiAllAccessBaseball::homeSchool.getTitle());
//    QAction* homePlayerEditor = new QAction("Edit Player Stats", this);
//    connect(homePlayerEditor, SIGNAL(triggered()), &homePlayerEdit, SLOT(updateSpinBoxes()));
//    connect(homePlayerEditor, SIGNAL(triggered()), &homePlayerEdit, SLOT(show()));
//    homeMenu->addAction(homePlayerEditor);
//    QAction* homeTeamEdit = new QAction("Edit Team Stats", this);
//    connect(homeTeamEdit, SIGNAL(triggered()), &homeEdit, SLOT(updateSpinBoxes()));
//    connect(homeTeamEdit, SIGNAL(triggered()), &homeEdit, SLOT(show()));
//    homeMenu->addAction(homeTeamEdit);
    QAction* scheduleEdit = new QAction("Schedule", this);
    connect(scheduleEdit, SIGNAL(triggered(bool)), &scheduleGui, SLOT(show()));
    homeMenu->addAction(scheduleEdit);

    QMenu* lowerThirdMenu = new QMenu("Lower Third");
    QAction* customLtCreator = new QAction("Create custom Lt", this);
    connect(customLtCreator, SIGNAL(triggered()), &ltCreator, SLOT(show()));
    customLtCreator->setShortcut(Qt::CTRL + Qt::Key_1);
    lowerThirdMenu->addAction(customLtCreator);


    //menuBar()->addMenu(awayMenu);
    menuBar()->addMenu(nchcMenu);
    menuBar()->addMenu(homeMenu);
    //menuBar()->addMenu(lowerThirdMenu);


}

void MainWindow::attachGraphicToHide(Graphic *graphic)
{
    panel.getDispControls()->addGraphicToHide(graphic);
}
