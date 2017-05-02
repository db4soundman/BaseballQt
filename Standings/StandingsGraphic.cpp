#include "StandingsGraphic.h"
#include <QGraphicsScene>
#include "MiamiAllAccessBaseball.h"

StandingsGraphic::StandingsGraphic(QGraphicsRectItem* parent) :
    QGraphicsRectItem(parent) {
    setRect(0,0,430,750);
    show = false;
    macLogo = MiamiAllAccessBaseball::getImgFromResources(":/images/MAC.png",50);
    prepareColor();
}

void StandingsGraphic::paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
                             QWidget* widget) {
    if (show) {
        painter->fillRect(0,0,rect().width(), rect().height(), bgGradient);
        int fontSize = 16;
        painter->setFont(QFont("Arial", fontSize, QFont::Bold));
        painter->setBrush(QColor(255,255,255));
        painter->setPen(QColor(255,255,255));
        //painter->fillRect(0,0,1920,1080, QColor(50,50,50));
        painter->drawText(100, 0, 230, 40, Qt::AlignCenter, "MAC STANDINGS");
        painter->drawPixmap(rect().width() - macLogo.width() - 30,0,macLogo);
        painter->setPen(QColor(253,180,26));
        painter->drawText(100, 50, 230, 40, Qt::AlignCenter, "EAST DIVISION");
        painter->drawText(100, 370, 230, 40, Qt::AlignCenter, "WEST DIVISION");
        fontSize = 14;
        painter->setFont(QFont("Arial", fontSize, QFont::Bold));
        painter->drawText(370, 50, 60, 40, Qt::AlignCenter, "OVR");
        painter->drawText(300, 50, 60, 40, Qt::AlignCenter, "CONF");
        painter->drawText(370, 370, 60, 40, Qt::AlignCenter, "OVR");
        painter->drawText(300, 370, 60, 40, Qt::AlignCenter, "CONF");
        painter->setPen(QColor(255,255,255));
        for (int i = 0; i < macStandings.size()/2; i++) {

            painter->drawText(35, 100 + (50*i), 240, 50, Qt::AlignRight | Qt::AlignVCenter, macStandings.at(i).getTeamName());
            painter->drawText(220, 100 + (50*i), 140, 50, Qt::AlignRight | Qt::AlignVCenter,
                              QString::number(macStandings.at(i).getWins())+"-"+ QString::number(macStandings.at(i).getLosses()));
            painter->drawText(370, 100 + (50*i), 55, 50, Qt::AlignRight | Qt::AlignVCenter,
                              QString::number(macStandings.at(i).getOvrWins())+"-"+ QString::number(macStandings.at(i).getOvrLosses()));
        }
        for (int i = macStandings.size()/2; i < macStandings.size(); i++) {

            painter->drawText(35, 170 + (50*i), 240, 50, Qt::AlignRight | Qt::AlignVCenter, macStandings.at(i).getTeamName());
            painter->drawText(220, 170 + (50*i), 140, 50, Qt::AlignRight | Qt::AlignVCenter,
                              QString::number(macStandings.at(i).getWins())+"-"+ QString::number(macStandings.at(i).getLosses()));
            painter->drawText(370, 170 + (50*i), 55, 50, Qt::AlignRight | Qt::AlignVCenter,
                              QString::number(macStandings.at(i).getOvrWins())+"-"+ QString::number(macStandings.at(i).getOvrLosses()));
        }
    }
}

void StandingsGraphic::updateStandings(QList<StandingsEntry> list)
{
    macStandings = list;
}

void StandingsGraphic::toggleShow()
{
    show = true;
    scene()->update(x(), y(), rect().width(), rect().height());
}

void StandingsGraphic::hideGraphic()
{
    if (show) {
        show = false;
        scene()->update(x(), y(), rect().width(), rect().height());
    }
}

void StandingsGraphic::prepareColor()
{
    bgGradient.setColorAt(0, QColor(50, 50, 50));
    bgGradient.setColorAt(1, QColor(20, 20, 20));
    bgGradient.setStart(0,0);
    bgGradient.setFinalStop(0,rect().height());

    QColor red(165, 0, 22, 200);
}
