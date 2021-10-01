#include "animatedbutton.h"

AnimatedButton::AnimatedButton(QString text, ROLE role, int radius, QWidget *parent)
    : AnimatedWidget(parent)
{
    if (text.size() > 0)
        setText(text);
    setRole(role);
    setRadius(radius);
}

void AnimatedButton::setFontParams(int font_size, bool bold)
{
    auto current_font = font();
    current_font.setBold(bold);
    current_font.setPointSize(font_size);
    setFont(current_font);
}

QSize AnimatedButton::sizeHint() const
{
    int h = 0;
    int w = 0;
    QString str(text_);
    bool empty = str.isEmpty();
    if (empty)
        str = QStringLiteral("XXXX");
    QFontMetrics fm = fontMetrics();
    QSize str_size = fm.size(Qt::TextShowMnemonic, str);
    if(!empty || !w)
        w = str_size.width();
    if(!empty || !h)
        h = str_size.height() * 2;
    return QSize(w, h);
}

void AnimatedButton::paintEvent(QPaintEvent *event)
{
    AnimatedWidget::paintEvent(event);
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::TextAntialiasing);

    if (state_ != STATE::NORMAL)
        painter.setBrush(QBrush(AppStyle::backgroundColor(role_, state_)));

    painter.setPen(QPen(AppStyle::textPrimaryColor()));
    painter.drawText(rect(), Qt::AlignCenter, text_);
}

