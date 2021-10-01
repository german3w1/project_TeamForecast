#ifndef DARKOVERLAYEFFECT_H
#define DARKOVERLAYEFFECT_H

#include <QPainter>
#include <QGraphicsEffect>

/**
@brief Dimming effect class
@details Implemented by overriding draw(QPainter *painter) function\n
Apply this effect to the widget you want to darken
*/

class DarkOverlayEffect : public QGraphicsEffect
{
public:
    DarkOverlayEffect(double opacity = 0.3);
private:
    double opacity_;
protected:
    /**
    @brief Overrided QGraphicEffect::draw
    @details Just darken the widget
    @see https://doc.qt.io/qt-6/qgraphicseffect.html#draw
    */
    void draw(QPainter *painter);
};

#endif // DARKOVERLAYEFFECT_H
