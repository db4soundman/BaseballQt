#include "MainWindow.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QAction>
#include <QMenu>
#include <QMenuBar>

MainWindow::MainWindow(BaseballGame* game, CommercialGraphic* comGraphic, PitcherGraphic *pg, DefenseGraphic *dg, BattingOrder *bog)
    : panel(game, comGraphic,pg, dg, bog),
    awayPlayerEdit(game, false), homePlayerEdit(game, true), awayEdit(game->getAwayTeam()), homeEdit(game->getHomeTeam()),
    ltCreator(game->getLt()) {
    setCentralWidget(&panel);
    //setMaximumWidth(800);
    //makeMenu(game);

}

MainWindow::~MainWindow() {

}

void MainWindow::makeMenu(BaseballGame* game)
{

    QMenu* awayMenu = new QMenu(game->getAwayName());
    QAction* awayPlayerEditor = new QAction("Edit Player Stats", this);
    connect(awayPlayerEditor, SIGNAL(triggered()), &awayPlayerEdit, SLOT(updateSpinBoxes()));
    connect(awayPlayerEditor, SIGNAL(triggered()), &awayPlayerEdit, SLOT(show()));
    awayMenu->addAction(awayPlayerEditor);
    QAction* awayTeamEdit = new QAction("Edit Team Stats", this);
    connect(awayTeamEdit, SIGNAL(triggered()), &awayEdit, SLOT(updateSpinBoxes()));
    connect(awayTeamEdit, SIGNAL(triggered()), &awayEdit, SLOT(show()));
    awayMenu->addAction(awayTeamEdit);

    QMenu* homeMenu = new QMenu(game->getHomeName());
    QAction* homePlayerEditor = new QAction("Edit Player Stats", this);
    connect(homePlayerEditor, SIGNAL(triggered()), &homePlayerEdit, SLOT(updateSpinBoxes()));
    connect(homePlayerEditor, SIGNAL(triggered()), &homePlayerEdit, SLOT(show()));
    homeMenu->addAction(homePlayerEditor);
    QAction* homeTeamEdit = new QAction("Edit Team Stats", this);
    connect(homeTeamEdit, SIGNAL(triggered()), &homeEdit, SLOT(updateSpinBoxes()));
    connect(homeTeamEdit, SIGNAL(triggered()), &homeEdit, SLOT(show()));
    homeMenu->addAction(homeTeamEdit);

    QMenu* lowerThirdMenu = new QMenu("Lower Third");
    QAction* customLtCreator = new QAction("Create custom Lt", this);
    connect(customLtCreator, SIGNAL(triggered()), &ltCreator, SLOT(show()));
    customLtCreator->setShortcut(Qt::CTRL + Qt::Key_1);
    lowerThirdMenu->addAction(customLtCreator);


    menuBar()->addMenu(awayMenu);
    menuBar()->addMenu(homeMenu);
    menuBar()->addMenu(lowerThirdMenu);


}
