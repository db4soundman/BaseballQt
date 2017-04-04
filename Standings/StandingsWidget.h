#ifndef STANDINGSWIDGET_H
#define STANDINGSWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QList>
#include <QComboBox>
#include <QSpinBox>
#include "StandingsGraphic.h"

class StandingsWidget : public QWidget {
    Q_OBJECT
public:
    StandingsWidget(StandingsGraphic* graphic);

signals:
    void shareStandings(QList<StandingsEntry> list);

private slots:
    void saveStandings();

private:
    QGridLayout* mainLayout;
    QList<QComboBox*> teamSelectors;
    QList<QSpinBox*> wins, losses, ties, shootoutWins;

private slots:
    void compileStandings();
};

#endif // STANDINGSWIDGET_H
