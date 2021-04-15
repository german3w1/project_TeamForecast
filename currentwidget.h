#ifndef CURRENTWIDGET_H
#define CURRENTWIDGET_H

#include <QJsonObject>
#include <expandingweatherwidget.h>

class CurrentWidget : public ExpandingWeatherWidget
{
public:
    CurrentWidget(QWidget *parent  = nullptr);
    void update_widget_info(const QVariantMap &new_dataset, const int &offset);
private:
    QLabel *m_time;
    QLabel *m_icon;
   // QLabel *m_sunrise;
   // QLabel *m_sunset;
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
};

#endif // CURRENTWIDGET_H
