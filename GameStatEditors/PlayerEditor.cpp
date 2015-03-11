#include "PlayerEditor.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QPushButton>

PlayerEditor::PlayerEditor(BaseballGame* game, bool homeTeam) {
    QVBoxLayout* mainLayout = new QVBoxLayout();
    QFormLayout* statsLayout = new QFormLayout();
    playerSelect.addItems(homeTeam ? game->getHomeTeam()->getGuiNames() :
                                     game->getAwayTeam()->getGuiNames());
    team = homeTeam ? game->getHomeTeam() : game->getAwayTeam();
    player = team->getPlayer(0);
    mainLayout->addWidget(&playerSelect);
    statsLayout->addRow("Goals", &goalsToday);
    statsLayout->addRow("Assits", &astToday);
    statsLayout->addRow("Penalties", &penaltiesToday);
    statsLayout->addRow("PIM Today", &pimToday);
    mainLayout->addLayout(statsLayout);
    QPushButton* ok = new QPushButton("Ok");
    connect(ok, SIGNAL(clicked()), this, SLOT(applyStats()));
    connect(ok, SIGNAL(clicked()), this, SLOT(hide()));
    mainLayout->addWidget(ok);
    setLayout(mainLayout);

    connect(&playerSelect, SIGNAL(currentIndexChanged(int)),
            this, SLOT(changePlayer(int)));
    setWindowTitle("Player Editor");
}

void PlayerEditor::updateSpinBoxes() {

}

void PlayerEditor::applyStats() {


}

void PlayerEditor::changePlayer(int index)
{
    player = team->getPlayer(index);
    updateSpinBoxes();
}
