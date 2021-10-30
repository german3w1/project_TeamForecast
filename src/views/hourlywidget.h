#ifndef HOURLYWIDGET_H
#define HOURLYWIDGET_H

#include <QJsonObject>
#include <src/models/hourlymodel.h>
#include <src/views/expandingweatherwidget.h>

/**
@brief Hourly weather forecast widget
*/

class HourlyWidget : public ExpandingWeatherWidget {
    Q_OBJECT
public:
    HourlyWidget(QWidget* parent = nullptr);
    ~HourlyWidget();
    void updateWidgetInfo(const HourlyModel& model);

private:
    QLabel* time;
    QLabel* day;
    QLabel* icon;
    QLabel* temp;
    QLabel* temp_value;
    QLabel* feels_like;
    QLabel* feels_like_value;
    QLabel* pressure_value;
    QLabel* humidity_value;
    QLabel* dew_point_value;
    QLabel* uv_ix_value;
    QLabel* clouds_value;
    QLabel* visibility_value;
    QLabel* wind_value;
    // QLabel *pop;
    // QLabel *pop_value;
};

#endif // HOURLYWIDGET_H
