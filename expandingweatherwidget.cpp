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



QString ExpandingWeatherWidget::getWindDirection(const int &degrees)
{
    if (degrees == 0) return "Северный";
    else if (0 < degrees && degrees < 90) return "Северо-Восточный";
    else if (degrees == 90) return "Восточный";
    else if (90 < degrees && degrees < 180) return "Юго-Восточный";
    else if (degrees == 180) return "Южный";
    else if (180 < degrees && degrees < 270) return "Юго-Западный";
    else if (degrees == 270) return "Западный";
    else return "Северо-Западный";
}

QPixmap ExpandingWeatherWidget::getWeatherIcon(const int &weather_id)
{
    QSize icon_size(48, 48);

    //перед просмотром этой группы switch смотри https://openweathermap.org/weather-conditions
    switch (weather_id / 100) { //чтобы сразу определить группу, к которой относятся погодные условия
        case 2: //2xx (Thunderstorm)
            return QIcon(":/weather_states/thunderstorm").pixmap(icon_size);
        case 3: //3xx (Drizzle)
            return QIcon(":/weather_states/shower_rain").pixmap(icon_size);
        case 5: //5xx (Rain)
            switch (weather_id) { //чтобы выбрать элемент внутри группы
                case 500: //fallthrough намеренно, чтобы покрыть случаи 500-504
                case 501:
                case 502:
                case 503:
                case 504:
                    return QIcon(":/weather_states/rain").pixmap(icon_size);
                case 511: //freezing_rain
                    return QIcon(":/weather_states/snow").pixmap(icon_size);
                case 520: //fallthrough намеренно, чтобы покрыть случаи 520, 521, 522 & 531
                case 521:
                case 522:
                case 531:
                    return QIcon(":/weather_states/shower_rain").pixmap(icon_size);
            }
            break; //чтобы не fallthrough
        case 6: //6хх (Snow)
            return QIcon(":/weather_states/snow").pixmap(icon_size);
        case 7: //7хх (Atmosphere)
            return QIcon(":/weather_states/mist").pixmap(icon_size);
        case 8: //8хх (Clear & Clouds)
            switch (weather_id) {
                case 800: //clear_sky
                    return QIcon(":/weather_states/clear_sky").pixmap(icon_size);
                case 801: //few_clouds
                    return QIcon(":/weather_states/few_clouds").pixmap(icon_size);
                case 802: //scattered_clouds
                    return QIcon(":/weather_states/scattered_clouds").pixmap(icon_size);
                case 803: //broken_clouds
                    return QIcon(":/weather_states/broken_clouds").pixmap(icon_size);
                case 804: //overcast_clouds
                    return QIcon(":/weather_states/overcast_clouds").pixmap(icon_size);
            }
    }
    return QIcon().pixmap(icon_size);
}


ExpandingWeatherWidget::~ExpandingWeatherWidget()
{

}
