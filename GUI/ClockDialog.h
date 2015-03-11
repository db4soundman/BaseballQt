#ifndef CLOCKDIALOG_H
#define CLOCKDIALOG_H

#include <QDialog>
#include "Clock.h"
#include <QSpinBox>

class ClockDialog : public QDialog {
    Q_OBJECT
public:
    ClockDialog(Clock* clock);

public slots:
    void accept();

private:
    Clock* clock;
    QSpinBox min, sec, tenths;
};

#endif // CLOCKDIALOG_H
