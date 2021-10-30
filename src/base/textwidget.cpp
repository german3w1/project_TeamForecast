#include "src/base/textwidget.h"

TextWidget::TextWidget(QString text, int size, bool bold, ROLE role, QWidget* parent)
    : BaseWidget(parent)
{
    if (text.size() > 0)
        setText(text);
    setRole(role);
    setFontParams(size, bold);
}

void TextWidget::setFontParams(int font_size, bool bold)
{
    auto current_font = font();
    current_font.setBold(bold);
    current_font.setPointSize(font_size);
    setFont(current_font);
}

QSize TextWidget::sizeHint() const
{
    int h = 0;
    int w = 0;
    QString str(text_);
    bool empty = str.isEmpty();
    if (empty)
        str = QStringLiteral("XXXX");
    QFontMetrics fm = fontMetrics();
    QSize str_size = fm.size(Qt::TextShowMnemonic, str);
    if (!empty || !w)
        w = str_size.width();
    if (!empty || !h)
        h = str_size.height();
    return QSize(w, h);
}

void TextWidget::paintEvent(QPaintEvent* event)
{
    BaseWidget::paintEvent(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::TextAntialiasing);
    painter.setBrush(QBrush(AppStyle::backgroundColor(role_, STATE::NORMAL)));
    painter.setPen(QPen(AppStyle::textPrimaryColor()));
    painter.drawText(rect(), align_, text_);
}
