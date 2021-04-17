#include "scrollareawrapper.h"
#include <QDebug>

ScrollAreaWrapper::ScrollAreaWrapper(QWidget *parent) : QScrollArea(parent)
{
    setFixedWidth(500);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    setAlignment(Qt::AlignHCenter);
    horizontalScrollBar()->setFixedSize(0,0);
    verticalScrollBar()->setFixedSize(0,0);
    setVerticalScrollBarPolicy (Qt :: ScrollBarAlwaysOff);
    setWidgetResizable(true);
    setObjectName("scroll_area");
    auto scroll_frame = new QFrame(this);
    scroll_frame->setObjectName("scroll_frame");
    scroll_frame->setContentsMargins(0,0,0,0);
    scroll_layout = new QVBoxLayout;
    scroll_frame->setLayout(scroll_layout);

    setWidget(scroll_frame);
}

