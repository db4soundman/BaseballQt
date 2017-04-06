#include "schedulegui.h"
#include <QTextStream>
#include <QFile>
#include "MiamiAllAccessBaseball.h"
#include <algorithm>
#include <QDate>
#include <QVBoxLayout>

#define MONTH 0
#define DAY 1
#define VS_AT 2
#define OPPONENT 3
#define TIME 4
#define STREAM 5

ScheduleGUI::ScheduleGUI()
{
    series.setText("Series View");
    series.setChecked(false);
    game.setText("Game View");
    game.setChecked(true);
    group.addButton(&series);
    group.addButton(&game);
    showButton.setText("Show");
    reloadButton.setText("Reload Schdule");
    QVBoxLayout* manager = new QVBoxLayout();
    manager->addWidget(&numToShow);
//    manager->addWidget(&series);
//    manager->addWidget(&game);
    manager->addWidget(&reloadButton);
    manager->addWidget(&showButton);

    loadSchedule();
    numToShow.setMinimum(1);

    connect(&showButton, SIGNAL(clicked()), this, SLOT(prepareToShow()));
    connect(&showButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(&reloadButton, SIGNAL(clicked(bool)), this, SLOT(loadSchedule()));
    setLayout(manager);
}

void ScheduleGUI::loadSchedule()
{
    QFile csv(MiamiAllAccessBaseball::getAppDirPath() + "/schedule.csv");
    csv.open(QIODevice::ReadOnly);
    QTextStream stream(&csv);
    stream.readLine();
    const int month = QDate::currentDate().month();
    const int date = QDate::currentDate().day();
    schedule.clear();
    while (!stream.atEnd()) {
        QStringList data = stream.readLine().split(',');
        QString tMonth = data[MONTH].split('/')[0];
        int schedMonth = QDate::fromString(tMonth, "MMM").month();
        int day1 = data[DAY].split('/')[0].toInt();
        int day2 = data[DAY].contains("/") ? data[DAY].split('/')[1].toInt():
                -1;
        // Same month, look at days
        if (schedMonth == month) {
            if (date < day1) {
                ScheduleEntry entry(data[MONTH],1,QString::number(day1),data[VS_AT],
                        data[OPPONENT], data[TIME], data[STREAM]);//, QString::number(day2), data[6], data[8]);
                schedule.append(entry);
            } else if ( date < day2) {
                ScheduleEntry entry(data[0],1,QString::number(day2),data[3],
                        data[4], data[6], data[8]);
                schedule.append(entry);
            }
        }
        // schedMonth in future
        else if ( month < schedMonth ) {
            ScheduleEntry entry(data[MONTH],1,QString::number(day1),data[VS_AT],
                    data[OPPONENT], data[TIME], data[STREAM]);//, QString::number(day2), data[6], data[8]);
            schedule.append(entry);
        }
    }
    numToShow.setValue(std::min(2, schedule.length()));
    numToShow.setMaximum(std::min(8, schedule.length()));
}

void ScheduleGUI::prepareToShow()
{
    int num = numToShow.value();
    QList<ScheduleEntry> toShow;
    for (int i = 0; toShow.size() <  num; i++) {
        if (series.isChecked()) {
            toShow.append(schedule[i]);
        }
        else {
            ScheduleEntry temp = schedule[i];
            toShow.append(temp);
            if (temp.getNumGames() == 2 && (i + 1) < num) {
                ScheduleEntry part2(temp.getMonth2().isEmpty() ? temp.getMonth1() : temp.getMonth2(),
                                    1,temp.getDate2(), temp.getVsAt(), temp.getOpp(),
                                    temp.getTime2(),temp.getMedia2());
                toShow.append(part2);
            //    i++;
            }
        }
    }
    emit show(toShow, series.isChecked());
}
