#include "scrollareawrapper.h"

ScrollAreaWrapper::ScrollAreaWrapper(QWidget *parent) : QScrollArea(parent)
{
    setFixedWidth(500);
    setStyleSheet("QFrame {background: white; border: 0px; border-radius: 20px;}");
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    setAlignment(Qt::AlignHCenter);
    horizontalScrollBar()->setFixedSize(0,0);
    verticalScrollBar()->setFixedSize(0,0);
    setVerticalScrollBarPolicy (Qt :: ScrollBarAlwaysOff);
    setWidgetResizable(true);

    auto scroll_frame = new QFrame(this);
    scroll_frame->setContentsMargins(0,0,0,0);
    scroll_layout = new QVBoxLayout;
    scroll_frame->setLayout(scroll_layout);

    setWidget(scroll_frame);
}

void ScrollAreaWrapper::addWidget(QWidget *widget) {
    scroll_layout->addWidget(widget);
}
