#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <QObject>

class Graphic : public QObject
{
    Q_OBJECT
public:
    Graphic(QObject *parent = 0);

public slots:

   // virtual void showGraphic() = 0;
    virtual void hideGraphic() = 0;
};

#endif // GRAPHIC_H
