#ifndef LOWERTHIRD_H
#define LOWERTHIRD_H

#include <QGraphicsRectItem>
#include <QLinearGradient>
#include <QPainter>
#include <QObject>
#include <QList>
#include <QString>
#include <QFont>
#include <QColor>

class LowerThird : public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    LowerThird(int screenWidth, QGraphicsItem* parent = 0);

    void paint(QPainter * painter,
               const QStyleOptionGraphicsItem * option, QWidget * widget = 0);



public slots:
    void hideLt();
    void showLt();
    void showPpComp();
    void prepareForDisplay(QString name, QString number, QString year, QList<QString> statLabels,
                           QList<QString> statValues, bool homeTeam, QString side="L");
    void prepareForCustomLt(QString name, QString number, QString year, QList<QString> statLabels,
                           QList<QString> statValues, bool homeTeam);

private:
    QList<QString> statNames;
    QList<QString> statistics;
    QString name, number, year, firstName, lastName;
    QFont statFont, nameFont;
    QLinearGradient gradient, statGradient, homeNameGradient, awayNameGradient, homeStatGradient, awayStatGradient;

    QString homeName, awayName, homeLabel, awayLabel, homeStat, awayStat;

    void prepareColors();
    void prepareFontSize();
    void adjustFont();

    bool show, showPp;
    int fontPointSize, statFontPointSize, centerPoint;
};

#endif // LOWERTHIRD_H
