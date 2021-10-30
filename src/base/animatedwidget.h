#ifndef ANIMATEDWIDGET_H
#define ANIMATEDWIDGET_H

#include <QMouseEvent>
#include <QPainter>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QWidget>
#include <base/appstyle.h>
#include <base/basewidget.h>

class AnimatedWidget : public BaseWidget {
    Q_OBJECT
    Q_PROPERTY(int edge_r_ READ edgeR WRITE setEdgeR)
    Q_PROPERTY(int edge_l_ READ edgeL WRITE setEdgeL)
    Q_PROPERTY(bool selectable_ READ selectable WRITE setSelectable)

public:
    explicit AnimatedWidget(QWidget* parent = nullptr);
    int edge_r_;
    int edge_l_;
    bool from_left_;
    bool from_right_;
    int start_x_r_;
    int start_x_l_;
    int edgeR() const;
    void setEdgeR(const int& edge_r);
    int edgeL() const;
    void setEdgeL(const int& edge_l);
    bool selectable() const { return selectable_; }
    void setSelectable(bool selectable) { selectable_ = selectable; }
signals:
    void hovered();
    void pressed();
    void released();
    void clicked();

protected:
    STATE previous_state_;
    bool selectable_;
    virtual void paintEvent(QPaintEvent* event) override;
    virtual void mousePressEvent(QMouseEvent* event) override;
    virtual void mouseReleaseEvent(QMouseEvent* event) override;
    virtual void enterEvent(QEnterEvent* event) override;
    virtual void leaveEvent(QEvent* event) override;
    void animateWidget(int start_x_);
};

#endif // ANIMATEDWIDGET_H
