#include "animatedwidget.h"

AnimatedWidget::AnimatedWidget(QWidget *parent) : QWidget(parent)
{
    state_ = STATE::NORMAL;
}

int AnimatedWidget::edgeL() const
{
    return edge_l_;
}

void AnimatedWidget::setEdgeL(const int &edge_l)
{
    edge_l_ = edge_l;
    update();
}

int AnimatedWidget::edgeR() const
{
    return edge_r_;
}

void AnimatedWidget::setEdgeR(const int &edge_r)
{
    edge_r_ = edge_r;
    update();
}

void AnimatedWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(AppStyle::backgroundColor(role_, STATE::NORMAL)));
    painter.drawRoundedRect(rect(), r_, r_);

    if (state_ != STATE::NORMAL) {
        painter.setBrush(QBrush(AppStyle::backgroundColor(role_, state_)));
        if (from_right_) {
            QRect right_rect = rect();
            right_rect.setLeft(edge_l_);
            right_rect.setRight(start_x_r_);
            painter.drawRoundedRect(right_rect, r_,r_);
        }
        if (from_left_) {
            QRect left_rect = rect();
            left_rect.setLeft(start_x_l_);
            left_rect.setRight(edge_r_);
            painter.drawRoundedRect(left_rect, r_,r_);
        }
    }
}

void AnimatedWidget::mousePressEvent(QMouseEvent *event)
{

    state_ = STATE::PRESSED;
    emit pressed();

    animateWidget(event->pos().x());
}

void AnimatedWidget::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    if (state_ == STATE::PRESSED) {
        emit released();
        emit clicked();
        state_ = STATE::NORMAL;
        update();
    }

}

void AnimatedWidget::enterEvent(QEnterEvent *event)
{
    if (state_ == STATE::NORMAL && isEnabled()) {
        state_ = STATE::HOVERED;
        emit hovered();
        animateWidget(event->position().x());
    }
}

void AnimatedWidget::leaveEvent(QEvent *event)
{
    state_ = STATE::NORMAL;
    update();

}

void AnimatedWidget::animateWidget(int start_x_)
{
    auto w_rect = rect();
    if (start_x_ - w_rect.left() < r_ * 2) {
        from_left_  = true;
        from_right_ = false;
        start_x_l_ = w_rect.left();

        auto anim2 = new QPropertyAnimation(this, "edge_r_");
        anim2->setStartValue(start_x_l_ + 2 * r_);
        anim2->setEndValue(rect().right());
        anim2->setDuration(150);
        anim2->setEasingCurve(QEasingCurve::OutQuad);
        anim2->start(QAbstractAnimation::DeleteWhenStopped);
    }
    else if (w_rect.right() - start_x_ < r_ * 2) {
        from_right_ = true;
        from_left_ = false;
        start_x_r_ = w_rect.right();

        auto anim2 = new QPropertyAnimation(this, "edge_l_");
        anim2->setStartValue(start_x_r_ - 2 * r_);
        anim2->setEndValue(rect().left());
        anim2->setDuration(150);
        anim2->start(QAbstractAnimation::DeleteWhenStopped);
    }
    else {
        from_left_ = true;
        from_right_ = true;
        start_x_l_ = start_x_ - r_;
        start_x_r_ = start_x_ + r_;
        auto group = new QParallelAnimationGroup(this);
        auto anim1 = new QPropertyAnimation(this, "edge_l_");
        anim1->setStartValue(start_x_l_);
        anim1->setEndValue(rect().left());
        anim1->setDuration(150);
        group->addAnimation(anim1);
        auto anim2 = new QPropertyAnimation(this, "edge_r_");
        anim2->setStartValue(start_x_r_);
        anim2->setEndValue(rect().right());
        anim2->setDuration(150);
        group->addAnimation(anim2);
        group->start(QAbstractAnimation::DeleteWhenStopped);
    }


}
