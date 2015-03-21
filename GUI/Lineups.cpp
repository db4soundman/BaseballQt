#include "Lineups.h"
#include <QGridLayout>
Lineups::Lineups(BaseballGame *game)
{
    QStringList positions;
    positions.append("P");
    positions.append("C");
    positions.append("1B");
    positions.append("2B");
    positions.append("SS");
    positions.append("3B");
    positions.append("LF");
    positions.append("CF");
    positions.append("RF");
    positions.append("DH");
    positions.append("PH");
    positions.append("PR");

    QGridLayout* myLayout = new QGridLayout();

    myLayout
}
