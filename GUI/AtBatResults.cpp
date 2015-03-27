#include "AtBatResults.h"
#include <QGridLayout>

AtBatResults::AtBatResults(BaseballGame* game) {
    QGridLayout* main = new QGridLayout();
    single.setText("1B");
    double2b.setText("2B");
    triple.setText("3B");
    homeRun.setText("HR");
    walk.setText("Walk");
    hbp.setText("HBP");
    strikeout.setText("K");
    reachedOnError.setText("E");
    fieldersChoice.setText("FC");
    genOut.setText("GO/FO");
    sacrifice.setText("Sac B/F");
    doublePlay.setText("DP");

    connect(&single, SIGNAL(clicked()), game, SLOT(single()));
    connect(&double2b, SIGNAL(clicked()), game, SLOT(double2b()));
    connect(&triple, SIGNAL(clicked()), game, SLOT(triple()));
    connect(&homeRun, SIGNAL(clicked()), game, SLOT(homeRun()));
    connect(&walk, SIGNAL(clicked()), game, SLOT(walk()));
    connect(&hbp, SIGNAL(clicked()), game, SLOT(hitByPitch()));
    connect(&strikeout, SIGNAL(clicked()), game, SLOT(strikeOut()));
    connect(&reachedOnError, SIGNAL(clicked()), game, SLOT(reachOnError()));
    connect(&fieldersChoice, SIGNAL(clicked()), game, SLOT(fielderChoice()));
    connect(&genOut, SIGNAL(clicked()), game, SLOT(genOut()));
    connect(&sacrifice, SIGNAL(clicked()), game, SLOT(sacrifice()));
    connect(&doublePlay, SIGNAL(clicked()), game, SLOT(doublePlay()));

    main->addWidget(&single, 0, 0);
    main->addWidget(&homeRun, 0,3);
    main->addWidget(&double2b, 0,1);
    main->addWidget(&walk, 1,1);
    main->addWidget(&triple, 0, 2);
    main->addWidget(&hbp, 1, 2);
    main->addWidget(&strikeout, 1, 0);
    main->addWidget(&reachedOnError, 1, 3);
    main->addWidget(&genOut, 2, 0);
    main->addWidget(&fieldersChoice, 2, 1);
    main->addWidget(&doublePlay, 2, 2);
    main->addWidget(&sacrifice, 2, 3);
    main->setHorizontalSpacing(3);
    main->setVerticalSpacing(0);
    setLayout(main);



}
