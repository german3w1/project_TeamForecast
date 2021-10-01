#ifndef CURRENTWIDGET_H
#define CURRENTWIDGET_H

#include <QJsonObject>
#include <views/expandingweatherwidget.h>
#include <models/currentmodel.h>

/**
@brief Current weather forecast widget
*/

class CurrentWidget : public ExpandingWeatherWidget
{
    Q_OBJECT
public:
    CurrentWidget(QWidget *parent  = nullptr);
    ~CurrentWidget();
    void updateWidgetInfo(const CurrentModel &model);
private:
    QLabel *time; ///< current time field
    QLabel *icon; ///< icon of current weather
   // QLabel *sunrise;
   // QLabel *sunset;
    QLabel *temp; ///< current temp label
    QLabel *temp_value; ///< current temp value field
    QLabel *feels_like; ///< current feels like label
    QLabel *feels_like_value; ///< current feels like value field

    QLabel *pressure_value; ///< current pressure value field
    QLabel *humidity_value; ///< current humidity value field
    QLabel *dew_point_value; ///< current dew-point value field
    QLabel *uv_ix_value; ///< current UV-index value field
    QLabel *clouds_value; ///< current cloudness value field
    QLabel *visibility_value; ///< current visibility value field
    QLabel *wind_value; ///< current wind speed and direction values field
};

#endif // CURRENTWIDGET_H
