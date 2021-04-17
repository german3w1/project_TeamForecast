#ifndef DARKOVERLAYEFFECT_H
#define DARKOVERLAYEFFECT_H

#include <QPainter>
#include <QGraphicsEffect>

class DarkOverlayEffect : public QGraphicsEffect
{
public:
    DarkOverlayEffect();
protected:
    void draw(QPainter *painter);
};

#endif // DARKOVERLAYEFFECT_H
