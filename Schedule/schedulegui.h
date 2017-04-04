#ifndef SCHEDULEGUI_H
#define SCHEDULEGUI_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QRadioButton>
#include <QButtonGroup>
#include <QSpinBox>
#include "scheduleentry.h"

class ScheduleGUI : public QWidget
{
    Q_OBJECT
public:
    ScheduleGUI();

signals:
    void show(QList<ScheduleEntry> games, bool seriesSched);

private slots:
    void prepareToShow();

private:
    QButtonGroup group;
    QRadioButton series, game;
    QPushButton showButton;
    QSpinBox numToShow;
    QList<ScheduleEntry> schedule;
};

#endif // SCHEDULEGUI_H
