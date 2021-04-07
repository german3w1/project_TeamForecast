#include "dailyforecast.h"
#include <QScrollBar>

DailyForecast::DailyForecast(QWidget *parent): QFrame(parent)
{
    m_main_layout = new QVBoxLayout(this);
    m_main_layout->setSpacing(4);
    m_main_layout->setContentsMargins(8, 8, 8, 40);
    setFixedWidth(500);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setStyleSheet("QFrame {background: white; border: 0px; border-radius: 20px;}");

    m_scroll_area = new QScrollArea(this);
    m_scroll_area->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    m_scroll_frame = new QFrame(m_scroll_area);
    m_scroll_frame->setContentsMargins(0,0,0,0);
    m_scroll_frame_layout = new QVBoxLayout(m_scroll_frame);

    auto daily_label = new QLabel("Прогноз на неделю", m_scroll_frame);
    daily_label->setStyleSheet("QLabel {font: bold 20px; color: black;}");
    m_scroll_frame_layout->addWidget(daily_label, 0, Qt::Alignment(Qt::AlignHCenter));
    for (auto i = 0; i < 8; i++) {
        m_daily_widgets[i] = new DailyWidget(m_scroll_frame);
        connect(m_daily_widgets[i], &DailyWidget::pressed, this, &DailyForecast::onWidgetPressed);
        m_scroll_frame_layout->addWidget(m_daily_widgets[i]);
    }

    m_scroll_frame->setLayout(m_scroll_frame_layout);
    m_scroll_area->setWidget(m_scroll_frame);
    m_scroll_area->setAlignment(Qt::AlignHCenter);
    m_scroll_area->horizontalScrollBar()->setFixedSize(0,0);
    m_scroll_area->verticalScrollBar()->setFixedSize(0,0);
    m_scroll_area->setVerticalScrollBarPolicy (Qt :: ScrollBarAlwaysOff);
    m_scroll_area->setWidgetResizable(true);
    m_main_layout->addWidget(m_scroll_area);
    setLayout(m_main_layout);
}

void DailyForecast::update_weather_info(const QList<QVariant> &new_daily_dataset, const int &offset) {
    for (auto i = 0; i < 8; i++)
        m_daily_widgets[i]->update_widget_info(new_daily_dataset[i].toMap(), offset);
}

void DailyForecast::onWidgetPressed(DailyWidget *widget){
    qDebug() << widget << "pressed";

    m_scroll_area->ensureWidgetVisible(widget);
}

DailyForecast::~DailyForecast(){

}
