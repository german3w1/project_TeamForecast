#ifndef TEXTWIDGET_H
#define TEXTWIDGET_H

#include <QPainter>
#include <src/base/appstyle.h>
#include <src/base/basewidget.h>

class TextWidget : public BaseWidget {
    Q_OBJECT
public:
    explicit TextWidget(QString text = "",
        int size = 10,
        bool bold = false,
        ROLE role = ROLE::PRIMARY,
        QWidget* parent = nullptr);
    void setText(const QString& text)
    {
        text_ = text;
        update();
    }
    QString text() const { return text_; }
    void setFontParams(int font_size, bool bold = false);
    QSize sizeHint() const override;
    void setAlignment(int qt_align_flag) { align_ = qt_align_flag; }

protected:
    virtual void paintEvent(QPaintEvent* event) override;

private:
    QString text_;
    ROLE role_;
    int align_;
};

#endif // TEXTWIDGET_H
