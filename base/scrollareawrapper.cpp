#include "base/scrollareawrapper.h"
#include <QDebug>
#include <base/appstyle.h>
#include <QPainter>

ScrollAreaWrapper::ScrollAreaWrapper(QWidget *parent) : QScrollArea(parent)
{
    //setFixedWidth(500);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    setAlignment(Qt::AlignHCenter);
    horizontalScrollBar()->setFixedSize(0,0);
    verticalScrollBar()->setFixedSize(0,0);
    setVerticalScrollBarPolicy (Qt :: ScrollBarAlwaysOff);
    setWidgetResizable(true);
    setObjectName("scroll_area");
    scroll_frame = new QFrame(this);
    scroll_frame->setObjectName("scroll_frame");   
    scroll_layout = new QVBoxLayout;
    //scroll_layout->setContentsMargins(0,0,0,0);
    scroll_frame->setLayout(scroll_layout);

    setWidget(scroll_frame);
}

void ScrollAreaWrapper::clear()
{
    while (QLayoutItem* item = scroll_layout->takeAt(0)) {
        item->widget()->deleteLater();
        delete item;
    }
}

