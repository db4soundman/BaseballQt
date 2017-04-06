#ifndef DISPLAYCONTROLS_H
#define DISPLAYCONTROLS_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include "BaseballGame.h"
#include "PitcherGraphic.h"
#include "CommercialGraphic.h"
#include "BattingOrder.h"
#include "DefenseGraphic.h"
#include "graphic.h"

class DisplayControls : public QWidget {
    Q_OBJECT
public:
    DisplayControls(BaseballGame* game,CommercialGraphic* comGraphic, PitcherGraphic* pg, DefenseGraphic* dg, BattingOrder* bog);
    void addGraphicToHide(Graphic* graphic);

public slots:
    void prepareCustomText();

signals:
    void showCustomText(QString text);

private:
    QLineEdit customtext;
    QPushButton customButton, announcersButton, commericalButton, sbButton, hideButton, sponsorButton, hideLT;
    QString sponsorText;
};

#endif // DISPLAYCONTROLS_H
