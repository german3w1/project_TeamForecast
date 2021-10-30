#ifndef BASEWIDGET_H
#define BASEWIDGET_H

#include <QPainter>
#include <QWidget>
#include <base/appstyle.h>

class BaseWidget : public QWidget {
    Q_OBJECT
public:
    explicit BaseWidget(QWidget* parent = nullptr);
    void setRole(ROLE role)
    {
        role_ = role;
        update();
    }
    ROLE role() { return role_; }
    void setRadius(int r)
    {
        r_ = r;
        update();
    }
    int radius() { return r_; }
    void setState(STATE state)
    {
        state_ = state;
        update();
    }
    STATE state() { return state_; }

protected:
    virtual void paintEvent(QPaintEvent*) override;
    int r_;
    ROLE role_;
    STATE state_;
};

#endif // BASEWIDGET_H
