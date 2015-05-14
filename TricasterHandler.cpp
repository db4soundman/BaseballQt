#include "TricasterHandler.h"
#include "AirSend_api.h"
#include <QHostAddress>
#include <QMessageBox>

TricasterHandler::TricasterHandler(QString ip, QGraphicsView *view, QColor pAlphaBlack) :
    alphaBlack(pAlphaBlack)
{
    screen = view;
    tricaster = AirSend_Create(1920, 1080,3000,1001,true, 16.0/9.0, false, 0,0);

    // Connect
    QHostAddress triCasterIp(ip);
    unsigned int blah = triCasterIp.toIPv4Address();
    AirSend_request_connection(tricaster, blah, 7001);
    /*tricaster = AirSend_Create(1920, 1080,3000,1001,false, 16.0/9.0, false, 0,0);
    // Connect
    QHostAddress ip("10.44.0.171");
    unsigned int blah = ip.toIPv4Address();
    AirSend_request_connection(tricaster, blah, 7000); */
    pixels = new BYTE[1920*1080*4];
    for (int i = 0; i < 1920*1080*4 - 1; i+=4) {
        ::memset(&pixels[i], 0, 1);
        ::memset(&pixels[i + 1], 0, 1);
        ::memset(&pixels[i + 2], 0, 1);
        ::memset(&pixels[i + 3], 0, 1);
    }
}

void TricasterHandler::srun() {
    //this->terminate();
    //this->wait();
    QPixmap img = QPixmap::grabWidget(screen);
    view = img.toImage();
    //::memset( &pixels[1920*1080*2], 0, 1920*1080*2);
     for (int i = 1920*1080*2; i < 1920*1080*4 - 1; i+=4) {
         QColor pixel = view.pixel(i/4 % 1920, i/4 / 1920);
         ::memset(&pixels[i], pixel.blue(), 1);
         ::memset(&pixels[i + 1], pixel.green(), 1);
         ::memset(&pixels[i + 2], pixel.red(), 1);
         ::memset(&pixels[i + 3], pixel == alphaBlack ? 0 : 255, 1);
     }
    //QColor c = view.pixel(1920/2, 1080-80-30);
  //  if (first) {
        start();
        //        first = false;
}

void TricasterHandler::ensureUpdate()
{
    QPixmap img = QPixmap::grabWidget(screen);
    view = img.toImage();
   // ::memset( &pixels[1920*1080*2], 0, 1920*1080*2);
     for (int i = 1920*1080*2; i < 1920*1080*4 - 1; i+=4) {
         QColor pixel = view.pixel(i/4 % 1920, i/4 / 1920);
         ::memset(&pixels[i], pixel.blue(), 1);
         ::memset(&pixels[i + 1], pixel.green(), 1);
         ::memset(&pixels[i + 2], pixel.red(), 1);
         ::memset(&pixels[i + 3], pixel == alphaBlack ? 0 : 255, 1);
     }
    //stopPoint = 5;
     start();
}

void TricasterHandler::updatePortion(int x, int y, int w, int h)
{
    QPixmap img = QPixmap::grabWidget(screen);
    view = img.toImage();
    int endX = x + w;
    for (int j = x; j < endX && j < 1920; j++) {
        int endY = y + h;
        for (int k = y; k < endY && k < 1080; k++) {
            QColor pixel = view.pixel(j, k);
            int arrIndex = (k * 1920 + j) * 4;
            ::memset(&pixels[arrIndex], pixel.blue(), 1);
            ::memset(&pixels[arrIndex+1], pixel.green(), 1);
            ::memset(&pixels[arrIndex+2], pixel.red(), 1);
            ::memset(&pixels[arrIndex+3], pixel == alphaBlack ? 0 : 255, 1);
        }
    }
    start();
}

void TricasterHandler::updatePortion(QList<QRectF> rects)
{
    QPixmap img = QPixmap::grabWidget(screen);
    view = img.toImage();
    bool redrawAlpha = false;
    for (int i = 0; i < rects.size(); i++) {
        int x = rects.at(i).x();
        int y = rects.at(i).y();
        int w = rects.at(i).width();
        int h = rects.at(i).height();
        int endX = x + w;
        for (int j = x; j < endX && j < 1920; j++) {
            int endY = y + h;
            for (int k = y; k < endY && k < 1080; k++) {
                QColor pixel = view.pixel(j, k);
                int arrIndex = (k * 1920 + j) * 4;
                ::memset(&pixels[arrIndex], pixel.blue(), 1);
                ::memset(&pixels[arrIndex+1], pixel.green(), 1);
                ::memset(&pixels[arrIndex+2], pixel.red(), 1);
                ::memset(&pixels[arrIndex+3], pixel == alphaBlack ? 0 : 255, 1);
            }
        }
        for (int r = 0; r < transparentRects.size() && !redrawAlpha; r++) {
            if (rects.at(i).contains(transparentRects.at(r)))
                redrawAlpha = true;
        }
    }
    if (redrawAlpha)
        drawTransparentRectangle();
    start();
}

void TricasterHandler::addAlphaRect(int x, int y, int w, int h)
{
    QRect r(x,y,w,h);
    if (!transparentRects.contains(r))
        transparentRects.append(r);
}

void TricasterHandler::removeAlphaRect(int x, int y, int w, int h)
{
    transparentRects.removeAll(QRect(x,y,w,h));
}

void TricasterHandler::drawTransparentRectangle()
{
    for (int i = 0; i < transparentRects.size(); i++) {
        int x = transparentRects.at(i).x();
        int y = transparentRects.at(i).y();
        int w = transparentRects.at(i).width();
        int h = transparentRects.at(i).height();
        int endX = x + w;
        for (int j = x; j < endX && j < 1920; j++) {
            int endY = y + h;
            for (int k = y; k < endY && k < 1080; k++) {
                QColor pixel = view.pixel(j, k);
                int arrIndex = (k * 1920 + j) * 4;
                ::memset(&pixels[arrIndex], pixel == alphaBlack ? 1 : pixel.blue(), 1);
                ::memset(&pixels[arrIndex+1],pixel == alphaBlack ? 1 : pixel.green(), 1);
                ::memset(&pixels[arrIndex+2], pixel == alphaBlack ? 1 : pixel.red(), 1);
                ::memset(&pixels[arrIndex+3], pixel == alphaBlack ? 128 : 255, 1);
            }
        }
    }
}

void TricasterHandler::run()
{
    for (int i = 0; i < 2; i++)
        AirSend_add_frame_bgra(tricaster, pixels);
}
