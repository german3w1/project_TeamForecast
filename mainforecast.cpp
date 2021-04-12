#include "mainforecast.h"

MainForecast::MainForecast(QWidget *parent) : QFrame(parent)
{
    m_main_layout = new QVBoxLayout(this);
    m_main_layout->setSpacing(4);
    m_main_layout->setContentsMargins(8, 8, 8, 40);
    setLayout(m_main_layout);
    setFixedWidth(500);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    setStyleSheet("QFrame {background: white; border: 0px; border-radius: 20px;}");

    m_scroll_area = new QScrollArea(this);
    m_main_layout->addWidget(m_scroll_area);

    m_scroll_frame = new QFrame(m_scroll_area);
    m_scroll_frame->setContentsMargins(0,0,0,0);

    m_scroll_frame_layout = new QVBoxLayout(m_scroll_frame);
    m_scroll_frame->setLayout(m_scroll_frame_layout);

    m_scroll_area->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    m_scroll_area->setWidget(m_scroll_frame);
    m_scroll_area->setAlignment(Qt::AlignHCenter);
    m_scroll_area->horizontalScrollBar()->setFixedSize(0,0);
    m_scroll_area->verticalScrollBar()->setFixedSize(0,0);
    m_scroll_area->setVerticalScrollBarPolicy (Qt :: ScrollBarAlwaysOff);
    m_scroll_area->setWidgetResizable(true);

    auto current_label = new QLabel("Текущая погода", m_scroll_frame);
    current_label->setStyleSheet("QLabel {font: bold 20px; color: black;}");
    current_label->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    m_scroll_frame_layout->addWidget(current_label, 0, Qt::Alignment(Qt::AlignHCenter));
    m_current_widget = new CurrentForecast(m_scroll_frame);
    m_scroll_frame_layout->addWidget(m_current_widget);

    auto hourly_label = new QLabel("Почасовой прогноз", m_scroll_frame);
    hourly_label->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    hourly_label->setStyleSheet("QLabel {font: bold 20px; color: black;}");
    m_scroll_frame_layout->addWidget(hourly_label, 0, Qt::Alignment(Qt::AlignHCenter));

    for (auto i = 0; i < 47; i++) {
        m_hourly_widgets[i] = new HourlyForecast(m_scroll_frame);
        connect(m_hourly_widgets[i], &HourlyForecast::pressed, this, &MainForecast::onHourlyWidgetPressed);
        m_scroll_frame_layout->addWidget(m_hourly_widgets[i]);

    }

}

void MainForecast::update_weather_info(const QVariantMap &new_current_dataset, const QList<QVariant> &new_hourly_dataset, const int &offset){
    m_current_widget->update_widget_info(new_current_dataset, offset);
    int today = QDateTime::fromSecsSinceEpoch(new_current_dataset["dt"].toLongLong(), Qt::OffsetFromUTC, offset).date().day();
    for (auto i = 0; i < 47; i++)
        m_hourly_widgets[i]->update_widget_info(new_hourly_dataset[i + 1].toMap(), today, offset);
}

void MainForecast::onHourlyWidgetPressed(ExpandingWeatherWidget *widget) {
    qDebug() << widget << "pressed";

    m_scroll_area->ensureWidgetVisible(widget);

};
