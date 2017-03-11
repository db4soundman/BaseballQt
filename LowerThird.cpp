#include "LowerThird.h"
#include <QFontMetrics>
#include <QStringRef>
#include <QGraphicsScene>
#include <QRect>

#define NAME_GRADIENT_LEVEL .5
#define STAT_GRADIENT_LEVEL .3
#define WIDTH 300
#define HEIGHT 250
#define NAME_HEIGHT 34
#define NAME_WIDTH 260
LowerThird::LowerThird(QColor awayColor, QColor homeColor, int screenWidth, QGraphicsItem* parent) : QGraphicsRectItem(parent),
    name(""), number("number"), statFont("Arial", 18, QFont::Bold), nameFont("Arial", 20, QFont::Bold),
    awayTeamMain(awayColor), homeTeamMain(homeColor) {
#ifdef Q_OS_OSX
    statFont.setPointSize(36);
    nameFont.setPointSize(36);
    #endif
    fontPointSize = nameFont.pointSize();
    setRect(0,0,WIDTH,HEIGHT);
    statFontPointSize = statFont.pointSize();
    gradient.setStart(0, 0);
    gradient.setFinalStop(0, NAME_HEIGHT);
    homeNameGradient.setStart(0, 0);
    homeNameGradient.setFinalStop(0, NAME_HEIGHT);
    awayNameGradient.setStart(0, 0);
    awayNameGradient.setFinalStop(0, NAME_HEIGHT);
    statGradient.setStart(0, NAME_HEIGHT);
    statGradient.setFinalStop(0, HEIGHT);
    homeStatGradient.setStart(0, NAME_HEIGHT);
    homeStatGradient.setFinalStop(0, HEIGHT);
    awayStatGradient.setStart(0, NAME_HEIGHT);
    awayStatGradient.setFinalStop(0, HEIGHT);
    prepareColors();
    statistics.append("");
    statNames.append("");
    this->centerPoint = screenWidth / 2;
    show = false;
    showPp = false;
}

void
LowerThird::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                  QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if (show) {
     //   painter->drawPixmap(0, 0, this->pixmap());
        painter->fillRect(0, 0, WIDTH, NAME_HEIGHT, gradient);
        painter->fillRect(0, NAME_HEIGHT, WIDTH, HEIGHT - NAME_HEIGHT, statGradient);

        painter->setPen(QColor(255,255,255));
        painter->setFont(nameFont);
        painter->drawText(25,0,NAME_WIDTH,NAME_HEIGHT, Qt::AlignCenter, name);
        painter->setFont(statFont);
        painter->drawText(0, 0, WIDTH, NAME_HEIGHT, Qt::AlignVCenter | Qt::AlignLeft, " " + number);
        painter->drawText(0, 0, WIDTH, NAME_HEIGHT, Qt::AlignVCenter | Qt::AlignRight, year + " ");
        painter->setFont(statFont);

       // int rectWidth = 800/statistics.size();

        // Stat Labels
        for (int i = 0; i< statNames.size(); i++) {
            painter->drawText(0, NAME_HEIGHT + 15 + i * 34, WIDTH/3, 24, Qt::AlignCenter, statNames.at(i));
            painter->drawText(2*WIDTH/3, NAME_HEIGHT + 15 + i * 34, WIDTH/3, 24, Qt::AlignCenter, statistics.at(i));
        }
    }
}

void
LowerThird::prepareForDisplay(QString name, QString number, QString year,
                              QList<QString> statLabels,
                              QList<QString> statValues, bool homeTeam, QString side) {
    this->name = name;
    if (name.contains(" ")) {
        firstName = name.left(name.indexOf(" "));
        QStringRef substr(&name, name.indexOf(" ") + 1, name.length() - (name.indexOf(" ")+1));
        lastName = substr.toString();
    }
    else {
        firstName = name;
        lastName = "";
    }
    this->year = year;
    this->number = number;

    if (side == "L") {
        setX(110);
    } else {
        setX(1600);
    }

    statNames = statLabels;
    statistics = statValues;
    gradient = homeTeam ? homeNameGradient : awayNameGradient;
    statGradient = homeTeam ? homeStatGradient : awayStatGradient;
    prepareFontSize();
    // To ensure font size is returned to normal in the event that
    // a custom text LT was used.
    statFont.setPointSize(statFontPointSize);
    showLt();
}

void LowerThird::prepareForCustomLt(QString name, QString number, QString year,
                                    QList<QString> statLabels,
                                    QList<QString> statValues, bool homeTeam)
{
    statFont.setPointSize(statFontPointSize);
    this->name = name;
    if (name.contains(" ")) {
        firstName = name.left(name.indexOf(" "));
        QStringRef substr(&name, name.indexOf(" ") + 1, name.length() - (name.indexOf(" ")+1));
        lastName = substr.toString();
    }
    else {
        firstName = name;
        lastName = "";
    }
    this->year = year;
    this->number = number;
    statNames = statLabels;
    statistics = statValues;
    //gradient = homeTeam ? homeNameGradient : awayNameGradient;
    statGradient = homeTeam ? homeStatGradient : awayStatGradient;
    // Resize the font to be two lines ONLY if necessary...
    QFontMetrics fontSize(statFont);
//    if (fontSize.width(statistics[0]) > this->pixmap().width() - 100)
//        adjustFont();
    showLt();
}


void LowerThird::prepareColors() {
    int red, green, blue;
    red = -1*homeTeamMain.red() *NAME_GRADIENT_LEVEL + homeTeamMain.red();
    green = -1*homeTeamMain.green() *NAME_GRADIENT_LEVEL + homeTeamMain.green();
    blue = -1*homeTeamMain.blue() *NAME_GRADIENT_LEVEL + homeTeamMain.blue();

    QColor end(red, green, blue);
    if (end == QColor(0,0,0))
        end = QColor(1,1,1);
    homeNameGradient.setColorAt(0, homeTeamMain);
    homeNameGradient.setColorAt(1, end);

    red = -1*homeTeamMain.red() *STAT_GRADIENT_LEVEL + homeTeamMain.red();
    green = -1*homeTeamMain.green() *STAT_GRADIENT_LEVEL + homeTeamMain.green();
    blue = -1*homeTeamMain.blue() *STAT_GRADIENT_LEVEL + homeTeamMain.blue();
    end.setRgb(red, green, blue);
    if (end == QColor(0,0,0))
        end = QColor(1,1,1);
    homeStatGradient.setColorAt(0, homeTeamMain);
    homeStatGradient.setColorAt(1, end);

// -------------------------------------Away Team--------------------------------

    red = -1*awayTeamMain.red() *NAME_GRADIENT_LEVEL + awayTeamMain.red();
    green = -1*awayTeamMain.green() *NAME_GRADIENT_LEVEL + awayTeamMain.green();
    blue = -1*awayTeamMain.blue() *NAME_GRADIENT_LEVEL + awayTeamMain.blue();
    end.setRgb(red, green, blue);
    if (end == QColor(0,0,0))
        end = QColor(1,1,1);
    awayNameGradient.setColorAt(0, awayTeamMain);
    awayNameGradient.setColorAt(1, end);

    red = -1*awayTeamMain.red() *STAT_GRADIENT_LEVEL + awayTeamMain.red();
    green = -1*awayTeamMain.green() *STAT_GRADIENT_LEVEL + awayTeamMain.green();
    blue = -1*awayTeamMain.blue() *STAT_GRADIENT_LEVEL + awayTeamMain.blue();
    end.setRgb(red, green, blue);
    if (end == QColor(0,0,0))
        end = QColor(1,1,1);
    awayStatGradient.setColorAt(0, awayTeamMain);
    awayStatGradient.setColorAt(1, end);

    gradient.setColorAt(0, QColor(50,50,50));
    gradient.setColorAt(1, QColor(25,25,25));
}

void
LowerThird::prepareFontSize() {
    int subtraction = 1;
    QFontMetrics fontSize(nameFont);
    while (fontSize.width(name) > NAME_WIDTH - 20) {
        QFont tempFont("Arial", fontPointSize - subtraction, QFont::Bold);
        //nameFont.setPointSize(fontPointSize - subtraction);
        subtraction++;
        nameFont = tempFont;
        QFontMetrics temp(nameFont);
        fontSize = temp;
    }
}

void LowerThird::adjustFont()
{
    statFont.setPointSize(22);
#ifdef Q_OS_OSX
    statFont.setPointSize(28);
#endif
    int subtraction = 1;
    QFontMetrics fontSize(statFont);
//    while (fontSize.width(statistics[0]) > this->pixmap().width() * 2 - 100) {
//        QFont tempFont("Arial", statFont.pointSize() - subtraction, QFont::Bold);
//        subtraction++;
//        statFont = tempFont;
//        QFontMetrics temp(statFont);
//        fontSize = temp;
//    }
}

void
LowerThird::hideLt() {
    if (show) {
        show = false;
        scene()->update();
    }
}

void
LowerThird::showLt() {
    show = true;
    scene()->update();
}

void LowerThird::showPpComp()
{

}
