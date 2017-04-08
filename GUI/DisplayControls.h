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
#include "LineScore.h"

class DisplayControls : public QWidget {
    Q_OBJECT
public:
    DisplayControls(BaseballGame* game,CommercialGraphic* comGraphic, LineScore* lineScore);
    void addGraphicToHide(Graphic* graphic);

public slots:
    void prepareCustomText();

signals:
    void showCustomText(QString text);

private:
    QLineEdit customtext;
    QPushButton customButton, announcersButton, commericalButton, sbButton, hideButton, sponsorButton, hideLT, lineScoreButton;
    QString sponsorText;
};

#endif // DISPLAYCONTROLS_H
