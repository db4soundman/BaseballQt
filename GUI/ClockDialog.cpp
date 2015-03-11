#include "ClockDialog.h"
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>

ClockDialog::ClockDialog(Clock* clock) {
    setWindowTitle("Set Game Clock");
    min.setMaximum(120);
    min.setMinimum(0);
    sec.setMaximum(60);
    sec.setMinimum(0);
    tenths.setMaximum(9);
    tenths.setMinimum(0);

    this->clock = clock;

    min.setValue(clock->getMinutes());
    sec.setValue(clock->getSeconds());
    tenths.setValue(clock->getTenths());

    QGridLayout* main = new QGridLayout();
    main->addWidget(new QLabel("M"), 0, 0);
    main->addWidget(new QLabel("S"), 0, 1);
    main->addWidget(new QLabel("T"), 0, 2);
    main->addWidget(&min, 1, 0);
    main->addWidget(&sec, 1, 1);
    main->addWidget(&tenths, 1, 2);



    QPushButton* ok = new QPushButton("OK");
    main->addWidget(ok, 2, 3);

    connect(ok, SIGNAL(clicked()), this, SIGNAL(accepted()));
    connect(this, SIGNAL(accepted()), this, SLOT(accept()));

    setLayout(main);
}

void ClockDialog::accept()
{
    clock->setClock(min.value(), sec.value(), tenths.value());
    this->close();
}
