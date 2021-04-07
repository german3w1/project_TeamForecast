#ifndef DAILYWIDGET_H
#define DAILYWIDGET_H

#include <QFrame>
#include <QWidget>
#include <QStyleOption>
#include <QPainter>
#include <QGridLayout>
#include <QJsonObject>
#include <QLabel>

class DailyWidget : public QWidget
{
    Q_OBJECT
public:
    DailyWidget(QWidget *parent);
    ~DailyWidget();
    void update_widget_info(const QVariantMap &new_dataset, const int &offset);
    QString getWindDirection(const int &degrees);
    void minimize();
    void maximize();
signals:
    void pressed(DailyWidget *widget);
private:
    bool expanded;
    QGridLayout* grid_layout;
    QLabel *m_day_of_week;
    QLabel *m_date;
   // QLabel *m_sunrise;
   // QLabel *m_sunset;
    QLabel *m_min_temp;
    QLabel *m_min_temp_value;
    QLabel *m_max_temp;
    QLabel *m_max_temp_value;

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
    QLabel *m_wind;
    QLabel *m_wind_value;

    QLabel *m_second_blank_space;
    QLabel *m_morn_temp;
    QLabel *m_morn_temp_value;
    QLabel *m_day_temp;
    QLabel *m_day_temp_value;
    QLabel *m_eve_temp;
    QLabel *m_eve_temp_value;
    QLabel *m_night_temp;
    QLabel *m_night_temp_value;
    QLabel *m_feels_like_label[4];
    QLabel *m_morn_fl_value;
    QLabel *m_day_fl_value;
    QLabel *m_eve_fl_value;
    QLabel *m_night_fl_value;

protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void paintEvent(QPaintEvent *event);
};

#endif // DAILYWIDGET_H
