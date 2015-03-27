#include "ClockControls.h"
#include <QVBoxLayout>
#include "ClockDialog.h"

ClockControls::ClockControls(BaseballGame* game, CommercialGraphic* comGraphic) {
    QVBoxLayout* main = new QVBoxLayout();
    label.setText("Clock Controls");
    advanceBatter.setText("Next Batter");
    nextPd.setText("Next Inning");
    prevPd.setText("Previous Inning");
    count.setText("Count");
    intermission.setText("INT");
    final.setText("FINAL");
    pitchingChange.setText("Pitching Change");
    main->addWidget(&label);    
    main->addWidget(&nextPd);
    main->addWidget(&prevPd);
    main->addWidget(&count);
    main->addWidget(&final);
    main->addWidget(&pitchingChange);
    main->addWidget(&advanceBatter);


    //connect(&run, SIGNAL(clicked()), game, SLOT(toggleClock()));
//    connect(game, SIGNAL(clockIsRunning(bool)),
//            this, SLOT(updateClockButton(bool)));
    //connect(&set, SIGNAL(clicked()), this, SLOT(showClockDialog()));
    connect(&pitchingChange, SIGNAL(clicked()), game->getSb(), SLOT(togglePitchingChange()));
    connect(&nextPd, SIGNAL(clicked()), game, SLOT(advancePeriod()));
    connect(&prevPd, SIGNAL(clicked()), game, SLOT(rewindPeriod()));

    connect(&count, SIGNAL(clicked()), game->getSb(), SLOT(displayClock()));
    connect(&count, SIGNAL(clicked()), comGraphic, SLOT(showClock()));
    connect(&final, SIGNAL(clicked()), game->getSb(), SLOT(final()));
    connect(&final, SIGNAL(clicked()), comGraphic, SLOT(finalTime()));
    connect(&advanceBatter, SIGNAL(clicked()), game, SLOT(advanceBatter()));
    setLayout(main);


}

void ClockControls::updateClockButton(bool clockIsRunning) {
    advanceBatter.setText( clockIsRunning ? "Stop Clock" : "Run Clock");
}

void ClockControls::showClockDialog()
{
    ClockDialog cd(gameClock);
    cd.exec();
}
