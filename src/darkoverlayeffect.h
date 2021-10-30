#ifndef DARKOVERLAYEFFECT_H
#define DARKOVERLAYEFFECT_H

#include <QGraphicsEffect>
#include <QPainter>

/**
@brief Dimming effect class
@details Implemented by overriding draw(QPainter *painter) function\n
Apply this effect to the widget you want to darken
*/

class DarkOverlayEffect : public QGraphicsEffect {
    Q_OBJECT
    Q_PROPERTY(double opacity_ READ opacity WRITE setOpacity)
public:
    DarkOverlayEffect(double opacity = 0.3);
    double opacity() { return opacity_; }
    void setOpacity(double opacity)
    {
        opacity_ = opacity;
        update();
    }

protected:
    /**
    @brief Overrided QGraphicEffect::draw
    @details Just darken the widget
    @see https://doc.qt.io/qt-6/qgraphicseffect.html#draw
    */
    void draw(QPainter* painter);

private:
    double opacity_;
};

#endif // DARKOVERLAYEFFECT_H
