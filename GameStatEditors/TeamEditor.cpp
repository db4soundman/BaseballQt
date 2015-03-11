#include "TeamEditor.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QFormLayout>

TeamEditor::TeamEditor(BaseballTeam* pTeam) {
    team = pTeam;
    setWindowTitle("Team Editor");
    QVBoxLayout* mainLayout = new QVBoxLayout();
    QFormLayout* spinBoxes = new QFormLayout();
    spinBoxes->addRow("Powerplay Goals Today", &ppg);
    spinBoxes->addRow("Powerplay Opp. Today", &ppopp);
    spinBoxes->addRow("Penalty Kills Today", &pk);
    spinBoxes->addRow("Penalty Kill Opp. Today", &pkopp);
    mainLayout->addLayout(spinBoxes);
    QPushButton* ok = new QPushButton("Ok");
    connect(ok, SIGNAL(clicked()), this, SLOT(changeStats()));
    connect(ok, SIGNAL(clicked()), this, SLOT(hide()));
    mainLayout->addWidget(ok);
    setLayout(mainLayout);


}

void TeamEditor::updateSpinBoxes()
{

}

void TeamEditor::changeStats()
{

}
