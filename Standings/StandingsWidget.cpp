#include "StandingsWidget.h"
#include <QStringList>
#include <QLabel>
#include <QPushButton>
#include <QFile>
#include "MiamiAllAccessBaseball.h"
#include <QTextStream>

StandingsWidget::StandingsWidget(StandingsGraphic* graphic) {
    mainLayout = new QGridLayout();
    QStringList east, west;
    // East Division
    east.append("BALL STATE");
    east.append("BOWLING GREEN");
    east.append("CENTRAL MICHIGAN");
   // east.append("BUFFALO");
    east.append("EASTERN MICHIGAN");
    east.append("KENT STATE");
    east.append("MIAMI");
    east.append("NORTHERN ILLINOIS");
    east.append("OHIO");
    east.append("TOLEDO");
    east.append("WESTERN MICHIGAN");

    // West Division
//    west.append("BALL STATE");
//    west.append("CENTRAL MICHIGAN");
//    west.append("EASTERN MICHIGAN");
//    west.append("NORTHERN ILLINOIS");
//    west.append("TOLEDO");
//    west.append("WESTERN MICHIGAN");
    mainLayout->addWidget(new QLabel("Team"), 0, 0);
    mainLayout->addWidget(new QLabel("Conf Wins"), 0, 1);
    mainLayout->addWidget(new QLabel("Conf Losses"), 0, 2);
    mainLayout->addWidget(new QLabel("Overall Wins"), 0, 3);
    mainLayout->addWidget(new QLabel("Overall Losses"), 0, 4);
    QList<QStringList> data;
//    QFile csv(MiamiAllAccessBaseball::getAppDirPath() + "/standings.txt");
//    csv.open(QIODevice::ReadWrite);
//    QTextStream stream(&csv);
//    while (!stream.atEnd()) {
//        data.append(stream.readLine().split(','));
//    }
//    csv.close();
    int x = 0;
//    for (int i = 0; i < data.size(); i++, x++) {
//        if (i == 0) {
//            mainLayout->addWidget(new QLabel("East Division"), x+1, 0);
//            x++;
//        }
//        if (i == east.size()) {
//            mainLayout->addWidget(new QLabel("West Division"), x+1, 0);
//            x++;
//        }
//        QComboBox* box = new QComboBox();
//        box->addItems(i < 5 ? east : west);
//        box->setCurrentText(data[i][0]);
//        teamSelectors.append(box);
//        QSpinBox* spin = new QSpinBox();
//        wins.append(spin);
//        spin->setValue(data[i][1].toInt());
//        spin = new QSpinBox();
//        losses.append(spin);
//        spin->setValue(data[i][2].toInt());
//        spin = new QSpinBox();
//        ovrWins.append(spin);
//        spin->setValue(data[i][3].isEmpty() ? 0 : data[i][2].toInt());
//        spin = new QSpinBox();
//        ovrLosses.append(spin);
//        spin->setValue(data[i][4].isEmpty() ? 0 : data[i][2].toInt());
//        mainLayout->addWidget(teamSelectors.at(i), x+1, 0);
//        mainLayout->addWidget(wins.at(i), x+1, 1);
//        mainLayout->addWidget(losses.at(i), x+1, 2);
//        mainLayout->addWidget(ovrWins.at(i), x+1, 3);
//        mainLayout->addWidget(ovrLosses.at(i), x+1, 4);
//    }
    if (data.size() == 0) {
        for(int i = 0; i < east.size() + west.size(); i++, x++) {
//            if (i == 0) {
//                mainLayout->addWidget(new QLabel("East Division"), x+1, 0);
//                x++;
//            }
//            if (i == east.size()) {
//                mainLayout->addWidget(new QLabel("West Division"), x+1, 0);
//                x++;
//            }
            QComboBox* box = new QComboBox();
            //box->addItems(i < 5 ? east : west);
            //box->setCurrentText(teams[0]);
            box->addItems(east);
            teamSelectors.append(box);
            QSpinBox* spin = new QSpinBox();
            wins.append(spin);
            spin->setValue(0);
            spin = new QSpinBox();
            losses.append(spin);
            spin->setValue(0);
            spin = new QSpinBox();
            ovrWins.append(spin);
            spin->setValue(0);
            spin = new QSpinBox();
            ovrLosses.append(spin);
            spin->setValue(0);
            mainLayout->addWidget(teamSelectors.at(i), x+1, 0);
            mainLayout->addWidget(wins.at(i), x+1, 1);
            mainLayout->addWidget(losses.at(i), x+1, 2);
            mainLayout->addWidget(ovrWins.at(i), x+1, 3);
            mainLayout->addWidget(ovrLosses.at(i), x+1, 4);
        }
    }
    QPushButton* closeButton = new QPushButton("Close");
    QPushButton* saveButton = new QPushButton("Save");
    QPushButton* showButton = new QPushButton("Show");
    connect(closeButton, SIGNAL(clicked()), this, SLOT(compileStandings()));
    connect(this, SIGNAL(shareStandings(QList<StandingsEntry>)),
            graphic, SLOT(updateStandings(QList<StandingsEntry>)));
    connect(saveButton, SIGNAL(clicked(bool)), this, SLOT(saveStandings()));
    connect(showButton, SIGNAL(clicked()), this, SLOT(compileStandings()));
    connect(showButton, SIGNAL(clicked()), graphic, SLOT(toggleShow()));
    mainLayout->addWidget(closeButton, x+1, 3);
    mainLayout->addWidget(saveButton, x+1, 4);
    mainLayout->addWidget(showButton, x+1, 5);
    setLayout(mainLayout);
}

void StandingsWidget::saveStandings()
{
    QFile csv(MiamiAllAccessBaseball::getAppDirPath() + "/standings.txt");
    csv.open(QIODevice::ReadWrite);
    QTextStream stream(&csv);
    for (int i = 0; i < teamSelectors.size(); i++) {
        stream << teamSelectors[i]->currentText() << "," << wins[i]->value()
               << "," << losses[i]->value()<<"," << ovrWins[i]->value()<<
               "," << ovrLosses[i]->value() << "\r\n";
    }
    csv.close();
}

void StandingsWidget::compileStandings()
{
    QList<StandingsEntry> standings;
    for (int i = 0; i < teamSelectors.size(); i++) {
        StandingsEntry temp(teamSelectors.at(i)->currentText(), wins.at(i)->value(),
                            losses.at(i)->value(), ovrWins[i]->value(), ovrLosses[i]->value());
        standings.append(temp);
    }
    emit shareStandings(standings);
    this->hide();
}
