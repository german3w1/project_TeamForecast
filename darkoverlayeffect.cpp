#include "darkoverlayeffect.h"

DarkOverlayEffect::DarkOverlayEffect()
{

}

void DarkOverlayEffect::draw( QPainter* painter ) {
    QPixmap pixmap;
    QPoint offset;
    if(sourceIsPixmap()) // No point in drawing in device coordinates (pixmap will be scaled anyways)
        pixmap = sourcePixmap( Qt::LogicalCoordinates, &offset );
    else // Draw pixmap in device coordinates to avoid pixmap scaling;
    {
        pixmap = sourcePixmap( Qt::DeviceCoordinates, &offset );
        painter->setWorldTransform( QTransform(), true);
    }
    painter->setBrush( QColor( 0, 0, 0, 255 ) ); // black bg
    painter->drawRect( pixmap.rect() );
    painter->setOpacity( 0.4 );
    painter->drawPixmap( offset, pixmap );
}
