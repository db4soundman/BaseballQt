#include "DisplayControls.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

DisplayControls::DisplayControls(BaseballGame* game, CommercialGraphic* comGraphic) {
    sponsorText = game->getSponsor();
    customtext.setReadOnly(false);
    customtext.setText("");
    hideLT.setText("Hide Stat Graphic");

    QVBoxLayout* main = new QVBoxLayout();

    QHBoxLayout* fr = new QHBoxLayout();
    fr->addWidget(&customtext, 1);
    customButton.setText("Custom Text");
    fr->addWidget(&customButton);
    sponsorButton.setText("Sponsor");
    fr->addWidget(&sponsorButton);
    announcersButton.setText("Announcers");
    fr->addWidget(&announcersButton);
    main->addLayout(fr);

    QHBoxLayout* sr = new QHBoxLayout();
    commericalButton.setText("Commercial");
    sbButton.setText("Scoreboard");
    hideButton.setText("Hide All");
    sr->addWidget(&commericalButton);
    sr->addWidget(&sbButton);
    sr->addWidget(&hideLT);
    sr->addWidget(&hideButton);
    main->addLayout(sr);

    setLayout(main);

    connect(&sponsorButton, SIGNAL(clicked()),
            game->getSb(), SLOT(displaySponsor()));
    connect(&announcersButton, SIGNAL(clicked()),
            game, SLOT(showAnnouncers()));
    connect(&customButton, SIGNAL(clicked()), this, SLOT(prepareCustomText()));
    connect(this, SIGNAL(showCustomText(QString)),
            game->getSb(), SLOT(changeTopBarText(QString)));
    connect(&commericalButton, SIGNAL(clicked()), comGraphic, SLOT(prepareAndShow()));
    connect(&commericalButton, SIGNAL(clicked()), game->getLt(), SLOT(hideLt()));
    connect(&commericalButton, SIGNAL(clicked()), game->getSb(), SLOT(hideBoard()));

    connect(&sbButton, SIGNAL(clicked()),
            game->getSb(), SLOT(toggleShowBoard()));

    connect(&sbButton, SIGNAL(clicked()),
            comGraphic, SLOT(hide()));

    connect(&hideLT, SIGNAL(clicked()), game->getLt(), SLOT(hideLt()));

    //hide
    connect(&hideButton, SIGNAL(clicked()), game->getSb(), SLOT(hideBoard()));
    connect(&hideButton, SIGNAL(clicked()), game->getLt(), SLOT(hideLt()));

    connect(&hideButton, SIGNAL(clicked()), comGraphic, SLOT(hide()));

}

void DisplayControls::prepareCustomText() {
    emit showCustomText(customtext.text());
}
