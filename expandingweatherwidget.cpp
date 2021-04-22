#include "expandingweatherwidget.h"

ExpandingWeatherWidget::ExpandingWeatherWidget(QWidget *parent) : QWidget(parent)
{
    auto main_layout = new QVBoxLayout;
    main_layout->setSpacing(0);
    setLayout(main_layout);
    setContentsMargins(4,4,4,4);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);

    unhidden_frame = new QWidget;
    unhidden_layout = new QGridLayout;
    unhidden_frame->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    unhidden_frame->setLayout(unhidden_layout);

    hidden_frame = new QWidget;
    hidden_layout = new QGridLayout;
    hidden_frame->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Ignored);
    hidden_frame->setLayout(hidden_layout);
    hidden_frame->setFixedHeight(0);

    main_layout->addWidget(unhidden_frame);
    main_layout->addWidget(hidden_frame);

    animation = new QPropertyAnimation(this, "hidden_height");
    animation->setDuration(200);
}

int ExpandingWeatherWidget::getHeight()
{
    return hidden_frame->height();
}

void ExpandingWeatherWidget::setHeight(int value)
{
    hidden_frame->setFixedHeight(value);
}

QLabel* ExpandingWeatherWidget::generateBoldLabel(const QString &text)
{
    auto label = new QLabel(text);
    label->setStyleSheet("QLabel {font: bold 14px; }");
    return label;
}

QLabel* ExpandingWeatherWidget::generatePaleLabel()
{
    auto label = new QLabel;
    label->setStyleSheet("QLabel {font: 14px }");
    return label;
}

//код, который я понятия не имею как работает, но указан в качестве
//обязательного в документации Qt при использовании stylesheets
void ExpandingWeatherWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void ExpandingWeatherWidget::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    if (hidden_frame->height() == 0){
        animation->setStartValue(0);
        animation->setEndValue(hidden_frame->sizeHint().height());
        animation->start();
    }
    else {
        animation->setStartValue(hidden_frame->height());
        animation->setEndValue(0);
        animation->start();
    }
   //emit pressed(this);
}

ExpandingWeatherWidget::~ExpandingWeatherWidget()
{

}
