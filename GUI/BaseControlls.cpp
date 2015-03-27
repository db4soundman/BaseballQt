#include "BaseControlls.h"
#include <QGridLayout>

BaseControlls::BaseControlls(BaseballGame *game)
{
    QGridLayout* myLayout = new QGridLayout();
    first.setText("1B: OFF");
    second.setText("2B: OFF");
    third.setText("3B: OFF");
    clear.setText("Clear Bases");

    myLayout->addWidget(&first, 1, 2);
    myLayout->addWidget(&second, 0, 1);
    myLayout->addWidget(&third, 1, 0);
    myLayout->addWidget(&clear, 2,1);

    connect(&first, SIGNAL(clicked()), game, SLOT(updateFirstBaseStatus()));
    connect(&second, SIGNAL(clicked()), game, SLOT(updateSecondBaseStatus()));
    connect(&third, SIGNAL(clicked()), game, SLOT(updateThirdBaseStatus()));
    connect(&clear, SIGNAL(clicked()), game, SLOT(clearBases()));

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

