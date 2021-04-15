#ifndef EXPANDINGWEATHERWIDGET_H
#define EXPANDINGWEATHERWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QStyleOption>
#include <QPainter>
#include <QPropertyAnimation>
#include <QLabel>

class ExpandingWeatherWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int hidden_height READ getHeight WRITE setHeight)
    Q_PROPERTY(QColor color READ color WRITE setColor)
public:
    ExpandingWeatherWidget(QWidget *parent = nullptr);

protected:
    QLabel* generateBoldLabel(const QString &text);
    QLabel* generatePaleLabel();
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void paintEvent(QPaintEvent *event);
    QGridLayout* unhidden_layout;    
    QGridLayout* hidden_layout;
private:
    QVBoxLayout* main_layout;
    QWidget* hidden_frame;
    QWidget* unhidden_frame;
    QPropertyAnimation *animation;
    int getHeight();
    void setHeight(int value);
    QColor color();
    void setColor(QColor color);
signals:
    void pressed(ExpandingWeatherWidget *widget);
private slots:   void setTheme();
    void onAnimationFinished();
};

#endif // EXPANDINGWEATHERWIDGET_H
