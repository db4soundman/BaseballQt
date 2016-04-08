#include "BaseControlls.h"
#include <QGridLayout>

BaseControlls::BaseControlls(BaseballGame *game)
{
    QGridLayout* myLayout = new QGridLayout();
    first.setText("1B: OFF");
    second.setText("2B: OFF");
    third.setText("3B: OFF");
    clear.setText("Clear Bases");
    firstSecond.setText("1B & 2B");
    firstThird.setText("1B & 3B");
    secondThird.setText("2B & 3B");
    loaded.setText("Bases Loaded");

    myLayout->addWidget(&first, 1, 2);
    myLayout->addWidget(&second, 0, 1);
    myLayout->addWidget(&third, 1, 0);
    myLayout->addWidget(&clear, 2,1);
    myLayout->addWidget(&firstSecond, 3,0);
    myLayout->addWidget(&firstThird, 4,0);
    myLayout->addWidget(&secondThird, 3, 1);
    myLayout->addWidget(&loaded, 4, 1);

    connect(&first, SIGNAL(clicked()), game, SLOT(updateFirstBaseStatus()));
    connect(&second, SIGNAL(clicked()), game, SLOT(updateSecondBaseStatus()));
    connect(&third, SIGNAL(clicked()), game, SLOT(updateThirdBaseStatus()));
    connect(&clear, SIGNAL(clicked()), game, SLOT(clearBases()));
    connect(&firstSecond, SIGNAL(clicked()), game, SLOT(makeFirstSecond()));
    connect(&firstThird, SIGNAL(clicked()), game, SLOT(makeFirstThird()));
    connect(&secondThird, SIGNAL(clicked()), game, SLOT(makeSecondThird()));
    connect(&loaded, SIGNAL(clicked()), game, SLOT(makeLoaded()));

    connect(game, SIGNAL(firstBaseStatus(bool)), this, SLOT(updateFirst(bool)));
    connect(game, SIGNAL(secondBaseStatus(bool)), this, SLOT(updateSecond(bool)));
    connect(game, SIGNAL(thirdBaseStatus(bool)), this, SLOT(updateThird(bool)));
    connect(game, SIGNAL(basesCleared()), this, SLOT(clearBases()));
    setLayout(myLayout);
}

void BaseControlls::updateFirst(bool on)
{
    QString text = "1B: ";
    text += on? "ON" : "OFF";
    first.setText(text);
}

void BaseControlls::updateSecond(bool on)
{
    QString text = "2B: ";
    text += on? "ON" : "OFF";
    second.setText(text);
}

void BaseControlls::updateThird(bool on)
{
    QString text = "3B: ";
    text += on? "ON" : "OFF";
    third.setText(text);
}

void BaseControlls::clearBases()
{
    updateFirst(false);
    updateSecond(false);
    updateThird(false);

}

