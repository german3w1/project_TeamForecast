#include "base/scrollareawrapper.h"

ScrollAreaWrapper::ScrollAreaWrapper(QWidget* parent)
    : QScrollArea(parent)
{
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    setAlignment(Qt::AlignHCenter);
    horizontalScrollBar()->setFixedSize(0, 0);
    verticalScrollBar()->setFixedSize(0, 0);
    setVerticalScrollBarPolicy(Qt ::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setWidgetResizable(true);
    scroll_frame = new BaseWidget;
    scroll_frame->setRole(ROLE::SECONDARY);
    scroll_layout = new QVBoxLayout;
    scroll_layout->setContentsMargins(4, 0, 4, 0);
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
