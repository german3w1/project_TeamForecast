#include "darkoverlayeffect.h"

DarkOverlayEffect::DarkOverlayEffect(double opacity)
{
    opacity_ = opacity;
}

void DarkOverlayEffect::draw(QPainter* painter)
{
    QPixmap pixmap;
    QPoint offset;
    if (sourceIsPixmap()) // No point in drawing in device coordinates (pixmap
        // will be scaled anyways)
        pixmap = sourcePixmap(Qt::LogicalCoordinates);
    else // Draw pixmap in device coordinates to avoid pixmap scaling;
    {
        pixmap = sourcePixmap(Qt::DeviceCoordinates);
        painter->setWorldTransform(QTransform(), true);
    }
    painter->setBrush(QColor(0, 0, 0, 255)); // black bg
    painter->drawRect(pixmap.rect());
    painter->setOpacity(opacity_);
    painter->drawPixmap(offset, pixmap);
}
