#include "BaseControlls.h"
#include <QGridLayout>

BaseControlls::BaseControlls(BaseballGame *game)
{
    setTitle("Base Controls");
    QGridLayout* myLayout = new QGridLayout();
    firstLabel.setText("1B: OFF");
    secondLabel.setText("2B: OFF");
    thirdLabel.setText("3B: OFF");
    first.setText("1B");
    second.setText("2B");
    third.setText("3B");
    clear.setText("Clear Bases");
    firstSecond.setText("1B-2B");
    firstThird.setText("1B-3B");
    secondThird.setText("2B-3B");
    loaded.setText("Bases Loaded");

    myLayout->addWidget(&firstLabel, 1, 2);
    myLayout->addWidget(&secondLabel, 0, 1);
    myLayout->addWidget(&thirdLabel, 1, 0);
    myLayout->addWidget(&clear, 2,1);
    myLayout->addWidget(&first, 3, 0);
    myLayout->addWidget(&second, 3, 1);
    myLayout->addWidget(&third, 3, 2);
    myLayout->addWidget(&firstSecond, 4,0);
    myLayout->addWidget(&firstThird, 5,0);
    myLayout->addWidget(&secondThird, 4, 1);
    myLayout->addWidget(&loaded, 5, 1);

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
    firstLabel.setText(text);
}

void BaseControlls::updateSecond(bool on)
{
    QString text = "2B: ";
    text += on? "ON" : "OFF";
    secondLabel.setText(text);
}

void BaseControlls::updateThird(bool on)
{
    QString text = "3B: ";
    text += on? "ON" : "OFF";
    thirdLabel.setText(text);
}

void BaseControlls::clearBases()
{
    updateFirst(false);
    updateSecond(false);
    updateThird(false);

}

