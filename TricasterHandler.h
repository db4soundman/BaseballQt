#ifndef TRICASTERHANDLER_H
#define TRICASTERHANDLER_H

//#define DEBUG

#include <QThread>
#include <QGraphicsView>
#include <QColor>
#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include "AirSend_api.h"
#include <QImage>
#include <QRectF>

class TricasterHandler : public QThread
{
    Q_OBJECT
public:
    TricasterHandler(QString ip, int port, QGraphicsView* view, QColor pAlphaBlack);
    ~TricasterHandler();
    void run();

signals:

public slots:
    void updatePortion(QList<QRectF> rects);
    void addAlphaRect(int x, int y, int w, int h);
    void removeAlphaRect(int x, int y, int w, int h);
    void addNoTransparencyZone(QRect r);
    void removeNoTransparencyZone(QRect r);

private:
    void drawTransparentRectangle();
    void* tricaster;
    QGraphicsView* screen;
    const QColor alphaBlack;
    BYTE* pixels;
    QImage view;
    QList<QRect> transparentRects;
    QList<QRect> noTransparencyZones;
#ifdef DEBUG
    int x;
#endif
};

#endif // TRICASTERHANDLER_H
