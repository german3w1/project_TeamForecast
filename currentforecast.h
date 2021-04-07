#ifndef CURRENTFORECAST_H
#define CURRENTFORECAST_H

#include <QWidget>
#include <QFrame>
#include <QLabel>
#include <QGridLayout>
#include <QJsonObject>

class CurrentForecast : public QFrame
{
public:
    CurrentForecast(QWidget *parent);
    void update_widget_info(const QVariantMap &new_dataset, const int &offset);
    QString getWindDirection(const int &degrees);
private:
    QGridLayout* grid_layout;
    QLabel *m_time;
   // QLabel *m_sunrise;
   // QLabel *m_sunset;
    QLabel *m_temp;
    QLabel *m_temp_value;
    QLabel *m_feels_like;
    QLabel *m_feels_like_value;
    QLabel *blank_space;
    QLabel *m_pressure;
    QLabel *m_pressure_value;
    QLabel *m_humidity;
    QLabel *m_humidity_value;
    QLabel *m_dew_point;
    QLabel *m_dew_point_value;
    QLabel *m_uv_ix;
    QLabel *m_uv_ix_value;
    QLabel *m_clouds;
    QLabel *m_clouds_value;
    QLabel *m_visibility;
    QLabel *m_visibility_value;
    QLabel *m_wind_speed;
    QLabel *m_wind_speed_value;
    QLabel *m_wind_deg;
    QLabel *m_wind_deg_value;
};

#endif // CURRENTFORECAST_H
