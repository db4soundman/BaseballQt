#include "CountControl.h"
#include <QString>
#include <QGridLayout>

CountControl::CountControl(BaseballGame* game) {
    setTitle("Count Controls");
    QGridLayout* main = new QGridLayout();
    outSub.setText("Out - 1");
    outPlus.setText("Out + 1");
    ballSub.setText("B - 1");
    ballThrown.setText("B + 1");
    strikeSub.setText("K - 1");
    strikeThrown.setText("K + 1");
    foul.setText("Foul + 1");
    foulSub.setText("Foul - 1");
    main->addWidget(&outSub,1,3);
    main->addWidget(&outPlus,0,3);
    main->addWidget(&ballSub, 1,0);
    main->addWidget(&ballThrown, 0,0);
    main->addWidget(&strikeSub, 1,1);
    main->addWidget(&strikeThrown, 0, 1);
    main->addWidget(&foul, 0, 2);
    main->addWidget(&foulSub, 1, 2);
//    main->setHorizontalSpacing(10);
//    main->setVerticalSpacing(0);


    connect(&ballSub, SIGNAL(clicked()), game, SLOT(subBallThrown()));
    connect(&strikeSub, SIGNAL(clicked()), game, SLOT(subStrikeThrown()));
    connect(&ballThrown, SIGNAL(clicked()), game, SLOT(ballThrown()));
    connect(&strikeThrown, SIGNAL(clicked()), game, SLOT(strikeThrown()));
    connect(&foul, SIGNAL(clicked()), game, SLOT(foulBall()));
    connect(&foulSub, SIGNAL(clicked()), game, SLOT(subFoulBall()));
    connect(&outSub, SIGNAL(clicked()), game, SLOT(subOut()));
    connect(&outPlus, SIGNAL(clicked()), game, SLOT(out()));


    setLayout(main);
}
