#ifndef HOURLYFORECAST_H
#define HOURLYFORECAST_H



#include <QEvent>
#include <QDebug>
#include <QJsonObject>
#include <expandingweatherwidget.h>

class HourlyForecast : public ExpandingWeatherWidget
{
public:
    HourlyForecast(QWidget *parent);
    ~HourlyForecast();
    void update_widget_info(const QVariantMap &new_dataset, const int &today, const int &offset);
private:
    QLabel *m_time;
    QLabel *m_day;
    QLabel *m_icon;
    QLabel *m_temp;
    QLabel *m_temp_value;
    QLabel *m_feels_like;
    QLabel *m_feels_like_value;
    QLabel *m_pressure_value;
    QLabel *m_humidity_value;
    QLabel *m_dew_point_value;
    QLabel *m_uv_ix_value;
    QLabel *m_clouds_value;
    QLabel *m_visibility_value;
    QLabel *m_wind_value;
   // QLabel *m_pop;
   // QLabel *m_pop_value;

};

#endif // HOURLYFORECAST_H
