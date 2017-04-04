#include "StandingsWidget.h"
#include <QStringList>
#include <QLabel>
#include <QPushButton>
#include <QFile>
#include "MiamiAllAccessBaseball.h"
#include <QTextStream>

StandingsWidget::StandingsWidget(StandingsGraphic* graphic) {
    mainLayout = new QGridLayout();
    QStringList teams;
    // East Division
    teams.append("BOWLING GREEN");
    teams.append("BUFFALO");
    teams.append("KENT STATE");
    teams.append("MIAMI");
    teams.append("OHIO");

    // West Division
    teams.append("BALL STATE");
    teams.append("CENTRAL MICHIGAN");
    teams.append("EASTERN MICHIGAN");
    teams.append("NORTHERN ILLINOIS");
    teams.append("TOLEDO");
    teams.append("WESTERN MICHIGAN");
    mainLayout->addWidget(new QLabel("Team"), 0, 0);
    mainLayout->addWidget(new QLabel("Wins"), 0, 1);
    mainLayout->addWidget(new QLabel("Losses"), 0 , 2);
    mainLayout->addWidget(new QLabel("Ties"), 0, 3);
    mainLayout->addWidget(new QLabel("SO/3x3 Wins"), 0, 4);
    QList<QStringList> data;
    QFile csv(MiamiAllAccessBaseball::getAppDirPath() + "/standings.txt");
    csv.open(QIODevice::ReadWrite);
    QTextStream stream(&csv);
    while (!stream.atEnd()) {
        data.append(stream.readLine().split(','));
    }
    csv.close();

    for (int i = 0; i < data.size(); i++) {
        QComboBox* box = new QComboBox();
        box->addItems(teams);
        box->setCurrentText(data[i][0]);
        teamSelectors.append(box);
        QSpinBox* spin = new QSpinBox();
        wins.append(spin);
        spin->setValue(data[i][1].toInt());
        spin = new QSpinBox();
        losses.append(spin);
        spin->setValue(data[i][2].toInt());
        spin = new QSpinBox();
        ties.append(spin);
        spin->setValue(data[i][3].toInt());
        spin = new QSpinBox();
        shootoutWins.append(spin);
        spin->setValue(data[i][4].toInt());
        mainLayout->addWidget(teamSelectors.at(i), i+1, 0);
        mainLayout->addWidget(wins.at(i), i+1, 1);
        mainLayout->addWidget(losses.at(i), i+1, 2);
        mainLayout->addWidget(ties.at(i), i+1, 3);
        mainLayout->addWidget(shootoutWins.at(i), i+1, 4);
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
    mainLayout->addWidget(closeButton, 9, 3);
    mainLayout->addWidget(saveButton, 9, 4);
    mainLayout->addWidget(showButton, 9, 5);
    setLayout(mainLayout);
}

void StandingsWidget::saveStandings()
{
    QFile csv(MiamiAllAccessBaseball::getAppDirPath() + "/standings.txt");
    csv.open(QIODevice::ReadWrite);
    QTextStream stream(&csv);
    for (int i = 0; i < teamSelectors.size(); i++) {
        stream << teamSelectors[i]->currentText() << "," << wins[i]->value()
               << "," << losses[i]->value() << "," << ties[i]->value()
               << "," << shootoutWins[i]->value() << "\r\n";
    }
    csv.close();
}

void StandingsWidget::compileStandings()
{
    QList<StandingsEntry> standings;
    for (int i = 0; i < teamSelectors.size(); i++) {
        StandingsEntry temp(teamSelectors.at(i)->currentText(), wins.at(i)->value(),
                            losses.at(i)->value(), ties.at(i)->value(), shootoutWins.at(i)->value());
        standings.append(temp);
    }
    emit shareStandings(standings);
    this->hide();
}
