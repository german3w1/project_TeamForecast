#ifndef DAILYWIDGET_H
#define DAILYWIDGET_H

#include <QJsonObject>
#include <models/dailymodel.h>
#include <views/expandingweatherwidget.h>

/**
@brief Daily weather forecast widget
*/

class DailyWidget : public ExpandingWeatherWidget {
    Q_OBJECT
public:
    DailyWidget(QWidget* parent = nullptr);
    ~DailyWidget();
    void updateWidgetInfo(const DailyModel& model);

private:
    QLabel* day_of_week;
    QLabel* date;
    QLabel* icon;
    // QLabel *sunrise;
    // QLabel *sunset;
    QLabel* min_temp;
    QLabel* min_temp_value;
    QLabel* max_temp;
    QLabel* max_temp_value;

    QLabel* pressure_value;
    QLabel* humidity_value;
    QLabel* dew_point_value;
    QLabel* uv_ix_value;
    QLabel* clouds_value;
    QLabel* visibility_value;
    QLabel* wind_value;

    QLabel* morn_temp_value;
    QLabel* day_temp_value;
    QLabel* eve_temp_value;
    QLabel* night_temp_value;
    QLabel* morn_fl_value;
    QLabel* day_fl_value;
    QLabel* eve_fl_value;
    QLabel* night_fl_value;
};

#endif // DAILYWIDGET_H
