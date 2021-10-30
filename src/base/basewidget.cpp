#include "src/base/basewidget.h"

BaseWidget::BaseWidget(QWidget* parent)
    : QWidget(parent)
{
    r_ = 0;
    state_ = STATE::NORMAL;
    role_ = ROLE::SECONDARY;
}

void BaseWidget::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(QBrush(AppStyle::backgroundColor(role_, state_)));
    painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(rect(), r_, r_);
}
