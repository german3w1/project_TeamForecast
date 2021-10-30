#ifndef ANIMATEDBUTTON_H
#define ANIMATEDBUTTON_H

#include "base/animatedwidget.h"

class AnimatedButton : public AnimatedWidget {
public:
    AnimatedButton(QString text = "",
        ROLE role = ROLE::PRIMARY,
        int radius = AppStyle::mediumCornerRadius(),
        QWidget* parent = nullptr);
    void setText(const QString& text)
    {
        text_ = text;
        update();
    }
    QString text() const { return text_; }
    void setFontParams(int font_size, bool bold = false);
    QSize sizeHint() const override;

protected:
    virtual void paintEvent(QPaintEvent* event) override;

private:
    QString text_;
};

#endif // ANIMATEDBUTTON_H
