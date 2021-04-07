#ifndef HOURLYFORECAST_H
#define HOURLYFORECAST_H


#include <QFrame>
#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QEvent>
#include <QDebug>
#include <QJsonObject>
#include <QStyleOption>
#include <QPainter>

class HourlyForecast : public QWidget
{
    Q_OBJECT
public:
    HourlyForecast(QWidget *parent);
    ~HourlyForecast();
    void update_widget_info(const QVariantMap &new_dataset, const int &today, const int &offset);
    QString getWindDirection(const int &degrees);
    void minimize();
    void maximize();
signals:
    void pressed(HourlyForecast *widget);
private:
    bool expanded;
    QGridLayout* grid_layout;
    QLabel *m_time;
    QLabel *m_day;
    QLabel *m_temp;
    QLabel *m_temp_value;
    QLabel *m_feels_like;
    QLabel *m_feels_like_value;
    QLabel *m_blank_space;
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
   // QLabel *m_pop;
   // QLabel *m_pop_value;
protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void paintEvent(QPaintEvent *event);
};

#endif // HOURLYFORECAST_H
