#include "MiamiAllAccessBaseball.h"

int main(int argc, char *argv[]) {
    MiamiAllAccessBaseball a(argc, argv);

//    BaseballTeam team;
//    QXmlSimpleReader reader;
//    SeasonXMLHandler handler(&team);
//    reader.setContentHandler(&handler);
//    reader.setErrorHandler(&handler);
//    QFile file (QFileDialog::getOpenFileName());
//    QXmlInputSource src(&file);
//    reader.parse(src);
//    int x = 4+4;
//    Scoreboard* sb = new Scoreboard(QColor(0,124,252), QColor(192,0,29));
//    QGraphicsScene* scene = new QGraphicsScene();
//    scene->addItem(sb);
//    LowerThird* lt = new LowerThird();
//    scene->addItem(lt);
//    lt->setY(740);
//    lt->setX(337);
//    QGraphicsView view(scene);

//    view.setFixedSize(1600,900);
//    view.setBackgroundBrush(QColor(0,120,0));
//    //view.showFullScreen();
//    view.setMinimumSize(1600,900);
//    //sb->setScale(1.68);
//   // sb->setPos(view.mapToScene(view.width()/2, -200));
//    sb->setY(80);
//    MainWindow w(sb);
//    view.showFullScreen();
//    w.show();

    return a.exec();
}
