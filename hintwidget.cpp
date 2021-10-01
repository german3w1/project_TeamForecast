#include "hintwidget.h"

HintWidget::HintWidget(QWidget *parent, const Hints &hints) : QWidget(parent), hints_(hints)
{

}

void HintWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(QBrush(AppStyle::backgroundColor(ROLE::SECONDARY, STATE::NORMAL)));
    painter.setPen(Qt::NoPen);
    painter.drawRect(rect());
    painter.setPen(AppStyle::textPrimaryColor());

    for (auto &[begin, end, text_pos, text] : hints_) {
        painter.drawLine(begin, end);
        painter.drawText(text_pos, text);
    }
}
