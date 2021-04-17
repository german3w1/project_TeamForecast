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
public:
    ExpandingWeatherWidget(QWidget *parent = nullptr);
    ~ExpandingWeatherWidget();
protected:
    QLabel* generateBoldLabel(const QString &text);
    QLabel* generatePaleLabel();
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void paintEvent(QPaintEvent *event);
    QGridLayout* unhidden_layout;    
    QGridLayout* hidden_layout;
private:
    QWidget* hidden_frame;
    QWidget* unhidden_frame;
    QPropertyAnimation *animation;
    int getHeight();
    void setHeight(int value);
signals:
    void pressed(ExpandingWeatherWidget *widget);
};

#endif // EXPANDINGWEATHERWIDGET_H
