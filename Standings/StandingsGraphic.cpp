#include "StandingsGraphic.h"
#include <QGraphicsScene>
#include "MiamiAllAccessBaseball.h"

StandingsGraphic::StandingsGraphic(QGraphicsRectItem* parent) :
    QGraphicsRectItem(parent) {
    setRect(0,0,1920,700);
    show = false;
    nchcLogo = MiamiAllAccessBaseball::getImgFromResources(":/images/NCHClrg.png",660);
    prepareColor();
}

void StandingsGraphic::paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
                             QWidget* widget) {
    if (show) {
        painter->fillRect(0,0,rect().width(), rect().height(), bgGradient);
        int fontSize = 24;
        painter->setFont(QFont("Arial", fontSize, QFont::Bold));
        painter->setBrush(QColor(255,255,255));
        painter->setPen(QColor(255,255,255));
        //painter->fillRect(0,0,1920,1080, QColor(50,50,50));
        painter->drawText(0, 0, 1920, 80, Qt::AlignCenter, "NCHC STANDINGS");
        painter->drawText(1200, 110, 140, 100, Qt::AlignRight | Qt::AlignVCenter, "W-L-T");
        painter->drawText(1320, 110, 140, 100, Qt::AlignRight | Qt::AlignVCenter, "PTS");
        painter->drawPixmap(100,0,nchcLogo);

        for (int i = 0; i < nchcStandings.size(); i++) {
            //painter->fillRect(0, 200 + (100*i), 1920, 50, QColor(165, 0, 22, 200));
            painter->drawText(400, 200 + (50*i), 700, 50, Qt::AlignRight | Qt::AlignVCenter, nchcStandings.at(i).getTeamName());
            painter->drawText(1200, 200 + (50*i), 140, 50, Qt::AlignRight | Qt::AlignVCenter,
                              QString::number(nchcStandings.at(i).getWins())+"-"+ QString::number(nchcStandings.at(i).getLosses())+"-"
                              + QString::number(nchcStandings.at(i).getTies()));
            painter->drawText(1320, 200 + (50*i), 140, 50, Qt::AlignRight | Qt::AlignVCenter, QString::number(nchcStandings.at(i).getPoints()));
        }
    }
}

void StandingsGraphic::updateStandings(QList<StandingsEntry> list)
{
    nchcStandings = list;
}

void StandingsGraphic::toggleShow()
{
    show = true;
    scene()->update();
}

void StandingsGraphic::hide()
{
    if (show) {
        show = false;
        scene()->update();
    }
}

void StandingsGraphic::prepareColor()
{
    bgGradient.setColorAt(0, QColor(41, 70, 91));
    bgGradient.setColorAt(1, QColor(23, 41, 53));
    bgGradient.setStart(0,0);
    bgGradient.setFinalStop(0,rect().height());

    QColor red(165, 0, 22, 200);
}
