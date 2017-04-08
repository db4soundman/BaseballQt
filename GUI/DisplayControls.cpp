#include "DisplayControls.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

DisplayControls::DisplayControls(BaseballGame* game, CommercialGraphic* comGraphic, LineScore *lineScore) {
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
    lineScoreButton.setText("Line Score");
    commericalButton.setText("Commercial");
    sbButton.setText("Scoreboard");
    hideButton.setText("Hide All");
    sr->addWidget(&lineScoreButton);
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

    connect(&lineScoreButton, SIGNAL(clicked(bool)), lineScore, SLOT(prepareAndShow()));
    connect(&lineScoreButton, SIGNAL(clicked()), game->getSb(), SLOT(hideBoard()));
    connect(&lineScoreButton, SIGNAL(clicked()), game->getLt(), SLOT(hideLt()));
    connect(&lineScoreButton, SIGNAL(clicked()), comGraphic, SLOT(hide()));

    connect(&commericalButton, SIGNAL(clicked()), comGraphic, SLOT(prepareAndShow()));
    connect(&commericalButton, SIGNAL(clicked()), game->getLt(), SLOT(hideLt()));
    connect(&commericalButton, SIGNAL(clicked()), game->getSb(), SLOT(hideBoard()));
    connect(&commericalButton, SIGNAL(clicked()), lineScore, SLOT(hideGraphic()));

    connect(&sbButton, SIGNAL(clicked()),game->getSb(), SLOT(toggleShowBoard()));
    connect(&sbButton, SIGNAL(clicked()), comGraphic, SLOT(hide()));
    connect(&sbButton, SIGNAL(clicked()), lineScore, SLOT(hideGraphic()));

    connect(&hideLT, SIGNAL(clicked()), game->getLt(), SLOT(hideLt()));

    //hide
    connect(&hideButton, SIGNAL(clicked()), game->getSb(), SLOT(hideBoard()));
    connect(&hideButton, SIGNAL(clicked()), game->getLt(), SLOT(hideLt()));
    connect(&hideButton, SIGNAL(clicked()), comGraphic, SLOT(hide()));
    connect(&hideButton, SIGNAL(clicked()), lineScore, SLOT(hideGraphic()));

}

void DisplayControls::addGraphicToHide(Graphic *graphic)
{
    connect(&hideButton,SIGNAL(clicked(bool)), graphic, SLOT(hideGraphic()));
    connect(&sbButton, SIGNAL(clicked()), graphic, SLOT(hideGraphic()));
    connect(&hideLT, SIGNAL(clicked()), graphic, SLOT(hideGraphic()));
    connect(&commericalButton, SIGNAL(clicked()), graphic, SLOT(hideGraphic()));
    connect(&lineScoreButton, SIGNAL(clicked()), graphic, SLOT(hideGraphic()));
}

void DisplayControls::prepareCustomText() {
    emit showCustomText(customtext.text());
}
