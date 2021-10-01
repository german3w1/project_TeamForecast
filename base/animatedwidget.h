#ifndef ANIMATEDWIDGET_H
#define ANIMATEDWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QMouseEvent>
#include <base/appstyle.h>

class AnimatedWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int edge_r_ READ edgeR WRITE setEdgeR )
    Q_PROPERTY(int edge_l_ READ edgeL WRITE setEdgeL )
public:
    explicit AnimatedWidget(QWidget *parent = nullptr);
    int edge_r_;
    int edge_l_;
    int r_;
    bool from_left_;
    bool from_right_;
    int start_x_r_;
    int start_x_l_;
    int edgeR() const;
    void setEdgeR(const int &edge_r);
    int edgeL() const;
    void setEdgeL(const int &edge_l);
signals:
    void hovered();
    void pressed();
    void released();
    void clicked();
protected:
    STATE state_;
    ROLE role_; 
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void enterEvent(QEnterEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;
    void animateWidget(int start_x_);
    void setRadius(int r)   { r_ = r; update(); }
    void setRole(ROLE role) { role_ = role; }
};

#endif // ANIMATEDWIDGET_H
