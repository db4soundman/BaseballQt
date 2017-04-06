#include "DisplayControls.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

DisplayControls::DisplayControls(BaseballGame* game, CommercialGraphic* comGraphic, PitcherGraphic *pg, DefenseGraphic *dg, BattingOrder *bog) {
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
    connect(&commericalButton, SIGNAL(clicked()), pg, SLOT(hideGraphic()));
    connect(&commericalButton, SIGNAL(clicked()), dg, SLOT(hideGraphic()));
    connect(&commericalButton, SIGNAL(clicked()), bog, SLOT(hideGraphic()));

    connect(&sbButton, SIGNAL(clicked()),game->getSb(), SLOT(toggleShowBoard()));
    connect(&sbButton, SIGNAL(clicked()), comGraphic, SLOT(hide()));
    connect(&sbButton, SIGNAL(clicked()), pg, SLOT(hideGraphic()));
    connect(&sbButton, SIGNAL(clicked()), dg, SLOT(hideGraphic()));
    connect(&sbButton, SIGNAL(clicked()), bog, SLOT(hideGraphic()));

    connect(&hideLT, SIGNAL(clicked()), game->getLt(), SLOT(hideLt()));
    connect(&hideLT, SIGNAL(clicked()), pg, SLOT(hideGraphic()));
    connect(&hideLT, SIGNAL(clicked()), dg, SLOT(hideGraphic()));
    connect(&hideLT, SIGNAL(clicked()), bog, SLOT(hideGraphic()));

    //hide
    connect(&hideButton, SIGNAL(clicked()), game->getSb(), SLOT(hideBoard()));
    connect(&hideButton, SIGNAL(clicked()), game->getLt(), SLOT(hideLt()));
    connect(&hideButton, SIGNAL(clicked()), comGraphic, SLOT(hide()));
    connect(&hideButton, SIGNAL(clicked()), pg, SLOT(hideGraphic()));
    connect(&hideButton, SIGNAL(clicked()), dg, SLOT(hideGraphic()));
    connect(&hideButton, SIGNAL(clicked()), bog, SLOT(hideGraphic()));

}

void DisplayControls::addGraphicToHide(Graphic *graphic)
{
    connect(&hideButton,SIGNAL(clicked(bool)), graphic, SLOT(hideGraphic()));
    connect(&sbButton, SIGNAL(clicked()), graphic, SLOT(hideGraphic()));
    connect(&hideLT, SIGNAL(clicked()), graphic, SLOT(hideGraphic()));
}

void DisplayControls::prepareCustomText() {
    emit showCustomText(customtext.text());
}
