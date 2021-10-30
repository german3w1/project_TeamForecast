#ifndef LOCATIONFORECAST_H
#define LOCATIONFORECAST_H

#include <QFrame>
#include <QHBoxLayout>
#include <QJsonDocument>
#include <QLabel>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QPainter>
#include <QPushButton>
#include <QRadioButton>
#include <QString>
#include <QVBoxLayout>
#include <QWidget>
#include <src/base/animatedbutton.h>
#include <src/base/scrollareawrapper.h>
#include <src/models/locationmodel.h>
#include <src/views/currentwidget.h>
#include <src/views/dailywidget.h>
#include <src/views/hourlywidget.h>

/**
@brief Widget implementing user location
@details Contains control panel showing current
latitude and longitude and allowing to edit or update
manually this location widget data
one ScrollAreaWrapper with current and hourly widgets,
one ScrollAreaWrapper with daily widgets
*/

class LocationForecast : public BaseWidget {
    Q_OBJECT
public:
    /**
    Constructs new location widget
    @param lat Latitude for new widget
    @param lon Longitude for new widget
    @param parent Parent of new widget
    */
    LocationForecast(const QString& lat, const QString& lon, QWidget* parent = nullptr);
    LocationForecast(QWidget* parent = nullptr);
    /**
    @brief Sets location widget latitude to lat
    */
    void setLat(const QString& lat);
    /**
    @brief Sets location longitude to lon
    */
    void setLon(const QString& lon);
    /**
    @brief Returns location latitude as QString
    */
    QString getLat();
    /**
    @brief Returns location widget longitude as QString
    */
    QString getLon();
    /**
    @brief Returns true whether the widget is a favorite, otherwise false
    */
    bool isFavorite();
    /**
    @brief Specifies whether the widget should be a favorite
    */
    void setFavorite(bool value);
    auto model() const { return model_; }

private:
    BaseWidget* forecasts_frame;
    BaseWidget* control_panel_frame;
    QRadioButton* favorite_checkbox;
    QLabel* last_update_time;
    QLabel* last_update_time_val; ///< location widget last successful update time value field. Part of control panel
    AnimatedButton* update_btn; ///< location widget update button. Part of control panel
    QLabel* latitude; ///< location latitude value field. Part of control panel
    QLabel* longitude; ///< location longitude value field. Part of control panel
    LocationModel* model_;
    CurrentWidget* current_widget; ///< current weather forecast widget
    HourlyWidget* hourly_widgets[47]; ///< hourly weather forecast widgets for next 47 hours
    DailyWidget* daily_widgets[7]; ///< daily weather forecast widgets for next 7 days
    void updateWeatherInfo();
signals:
    void modelChanged(LocationModel* model);
public slots:
    void weatherUpdateRequested();
    void setModel(LocationModel* model);
    void modelDestroyed();
private slots:
    void onEditBtnClicked();
    void onUpdateFinished();
    void onUpdateAborted();
};

#endif // LOCATIONFORECAST_H
