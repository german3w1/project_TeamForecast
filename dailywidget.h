#ifndef DAILYWIDGET_H
#define DAILYWIDGET_H

#include <QJsonObject>
#include <QLabel>
#include <expandingweatherwidget.h>

class DailyWidget : public ExpandingWeatherWidget
{
public:
    DailyWidget(QWidget *parent = nullptr);
    ~DailyWidget();
    void update_widget_info(const QVariantMap &new_dataset, const int &offset);
private:
    QLabel *m_day_of_week;
    QLabel *m_date;
    QLabel *m_icon;
   // QLabel *m_sunrise;
   // QLabel *m_sunset;
    QLabel *m_min_temp;
    QLabel *m_min_temp_value;
    QLabel *m_max_temp;
    QLabel *m_max_temp_value;

    QLabel *m_pressure_value;
    QLabel *m_humidity_value;
    QLabel *m_dew_point_value;
    QLabel *m_uv_ix_value;
    QLabel *m_clouds_value;
    QLabel *m_visibility_value;
    QLabel *m_wind_value;

    QLabel *m_morn_temp_value;
    QLabel *m_day_temp_value;
    QLabel *m_eve_temp_value;
    QLabel *m_night_temp_value;
    QLabel *m_morn_fl_value;
    QLabel *m_day_fl_value;
    QLabel *m_eve_fl_value;
    QLabel *m_night_fl_value;

};

#endif // DAILYWIDGET_H
