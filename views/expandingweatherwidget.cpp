#include "views/expandingweatherwidget.h"

ExpandingWeatherWidget::ExpandingWeatherWidget(QWidget *parent)
    : AnimatedWidget(parent)
{
    setRole(ROLE::PRIMARY);
    setRadius(AppStyle::biggestCornerRadius());
    auto main_layout = new QVBoxLayout;
    main_layout->setSpacing(0);
    setLayout(main_layout);
    main_layout->setContentsMargins(4,4,4,4);
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
    update();
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



void ExpandingWeatherWidget::mouseReleaseEvent(QMouseEvent *event)
{
    AnimatedWidget::mouseReleaseEvent(event);
    Q_UNUSED(event);

    if (auto height = hidden_frame->height(); height == 0){
        //animation->setStartValue(0);
        //animation->setEndValue(hidden_frame->sizeHint().height());
        //animation->start();
        hidden_frame->setFixedHeight(hidden_frame->sizeHint().height());
    }
    else {
        hidden_frame->setFixedHeight(0);
        //animation->setStartValue(height);
        //animation->setEndValue(0);
        //animation->start();
    }

}

ExpandingWeatherWidget::~ExpandingWeatherWidget()
{

}
