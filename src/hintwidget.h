#ifndef HINTWIDGET_H
#define HINTWIDGET_H
#include <QList>
#include <QPainter>
#include <QWidget>
#include <src/base/appstyle.h>

using Hints = QList<std::tuple<QPoint, QPoint, QPoint, QString>>;
class HintWidget : public QWidget {
public:
    HintWidget(QWidget* parent, const Hints& hints = {});
    void init(const Hints& hints) { hints_ = hints; }

protected:
    virtual void paintEvent(QPaintEvent* event) override;

private:
    Hints hints_;
};

#endif // HINTWIDGET_H
