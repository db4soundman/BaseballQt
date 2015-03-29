#include "ScoreControl.h"
#include <QGridLayout>

ScoreControl::ScoreControl(BaseballGame* game) {
    QGridLayout* main = new QGridLayout();
    title.setText("Score Controls");
    main->addWidget(&title, 0, 0);
    sm1.setText("- 1");
    sp1.setText("+ 1");
    sm2.setText("- 2");
    sp2.setText("+ 2");
    sm3.setText("- 3");
    sm4.setText("- 4");
    sp3.setText("+ 3");
    sp4.setText("+ 4");
    hm1.setText("H - 1");
    hp1.setText("H + 1");
    em1.setText("E - 1");
    ep1.setText("E + 1");

    main->addWidget(&sm1, 1, 0);
    main->addWidget(&sm2, 2, 0);
    main->addWidget(&sm3, 3, 0);
    main->addWidget(&sm4, 4, 0);
    main->addWidget(&sp1, 1, 1);
    main->addWidget(&sp2, 2, 1);
    main->addWidget(&sp3, 3, 1);
    main->addWidget(&sp4, 4, 1);
    main->addWidget(&hm1, 5,0);
    main->addWidget(&hp1, 5,1);
    main->addWidget(&em1, 6,0);
    main->addWidget(&ep1, 6,1);
    main->setHorizontalSpacing(3);
    main->setVerticalSpacing(0);
    setLayout(main);

    connect(&sm1, SIGNAL(clicked()), this, SLOT(down1()));
    connect(&sp1, SIGNAL(clicked()), this, SLOT(up1()));
    connect(&sm2, SIGNAL(clicked()), this, SLOT(down2()));
    connect(&sp2, SIGNAL(clicked()), this, SLOT(up2()));
    connect(&sm3, SIGNAL(clicked()), this, SLOT(down3()));
    connect(&sp3, SIGNAL(clicked()), this, SLOT(up3()));
    connect(&sm4, SIGNAL(clicked()), this, SLOT(down4()));
    connect(&sp4, SIGNAL(clicked()), this, SLOT(up4()));
    connect(&hm1, SIGNAL(clicked()), game, SLOT(subHit()));
    connect(&hp1, SIGNAL(clicked()), game, SLOT(addHit()));
    connect(&em1, SIGNAL(clicked()), game, SLOT(subError()));
    connect(&ep1, SIGNAL(clicked()), game, SLOT(addError()));
    connect(this, SIGNAL(changeScore(int)), game, SLOT(addScore(int)));


}

void ScoreControl::up1()
{
    emit changeScore(1);
}

void ScoreControl::down1()
{
    emit changeScore(-1);
}

void ScoreControl::up2()
{
    emit changeScore(2);
}

void ScoreControl::down2()
{
    emit changeScore(-2);
}

void ScoreControl::up3()
{
    emit changeScore(3);
}

void ScoreControl::down3()
{
    emit changeScore(-3);
}

void ScoreControl::up4()
{
    emit changeScore(4);
}

void ScoreControl::down4()
{
    emit changeScore(-4);
}
