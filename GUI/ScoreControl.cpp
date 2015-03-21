#include "ScoreControl.h"
#include <QGridLayout>

ScoreControl::ScoreControl(BaseballGame* game) {
    QGridLayout* main = new QGridLayout();
    title.setText("Score Controls");
    main->addWidget(&title, 0, 0);
    sm1.setText("- 1");
    sp1.setText("+ 1");
    sm2.setText("- 2");
    sp2.setText("+ 2");
    sm3.setText("- 3");
    sm4.setText("- 4");
    sp3.setText("+ 3");
    sp4.setText("+ 4");

    main->addWidget(&sm1, 1, 0);
    main->addWidget(&sm2, 2, 0);
    main->addWidget(&sm3, 3, 0);
    main->addWidget(&sm4, 4, 0);
    main->addWidget(&sp1, 1, 1);
    main->addWidget(&sp2, 2, 1);
    main->addWidget(&sp3, 3, 1);
    main->addWidget(&sp4, 4, 1);
    main->setHorizontalSpacing(3);
    main->setVerticalSpacing(0);
    setLayout(main);


}
