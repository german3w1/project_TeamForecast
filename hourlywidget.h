#ifndef HOURLYWIDGET_H
#define HOURLYWIDGET_H

#include <QDebug>
#include <QJsonObject>
#include <expandingweatherwidget.h>

class HourlyWidget : public ExpandingWeatherWidget
{
    Q_OBJECT
public:
    HourlyWidget(QWidget *parent = nullptr);
    ~HourlyWidget();
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

#endif // HOURLYWIDGET_H
