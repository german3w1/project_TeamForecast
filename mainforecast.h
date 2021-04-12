#ifndef MAINFORECAST_H
#define MAINFORECAST_H

#include <QFrame>
#include <QScrollArea>
#include <QScrollBar>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>
#include "currentforecast.h"
#include "hourlyforecast.h"

class MainForecast : public QFrame
{
public:
    MainForecast(QWidget *parent);
    void update_weather_info(const QVariantMap &new_current_dataset, const QList<QVariant> &new_hourly_dataset, const int &offset);
private:
    QVBoxLayout *m_main_layout;
    QFrame *m_scroll_frame;
    QVBoxLayout *m_scroll_frame_layout;
    QScrollArea *m_scroll_area;
    CurrentForecast *m_current_widget;
    HourlyForecast *m_hourly_widgets[47];
private slots:
    void onHourlyWidgetPressed(ExpandingWeatherWidget *widget);
};

#endif // MAINFORECAST_H
