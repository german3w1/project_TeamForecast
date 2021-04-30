#ifndef LOCATIONFORECAST_H
#define LOCATIONFORECAST_H

#include <QFrame>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QString>
#include <QPushButton>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QRadioButton>
#include <scrollareawrapper.h>
#include <currentwidget.h>
#include <hourlywidget.h>
#include <dailywidget.h>

/**
@brief Widget implementing user location
@details Contains control panel showing current
latitude and longitude and allowing to edit or update
manually this location widget data
one ScrollAreaWrapper with current and hourly widgets,
one ScrollAreaWrapper with daily widgets
*/

class LocationForecast : public QFrame
{
    Q_OBJECT
public:
    /**
    Constructs new location widget
    @param lat Latitude for new widget
    @param lon Longitude for new widget
    @param parent Parent of new widget
    */
    LocationForecast(const QString &lat, const QString &lon, QWidget* parent = nullptr);
    /**
    @brief Sets location widget latitude to lat
    */
    void setLat(const QString &lat);
    /**
    @brief Sets location longitude to lon
    */
    void setLon(const QString &lon);
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
private:
    bool previous_update_failed;
    QFrame *forecasts_frame;
    QFrame *control_panel_frame;
    QRadioButton *favorite_checkbox;
    QLabel *last_update_time;
    QLabel *last_update_time_val; ///< location widget last successful update time value field. Part of control panel
    QPushButton *update_btn; ///< location widget update button. Part of control panel
    QNetworkAccessManager *network_manager;
    QLabel* latitude; ///< location latitude value field. Part of control panel
    QLabel* longitude; ///< location longitude value field. Part of control panel
    CurrentWidget *current_widget; ///< current weather forecast widget
    HourlyWidget *hourly_widgets[47]; ///< hourly weather forecast widgets for next 47 hours
    DailyWidget *daily_widgets[7]; ///< daily weather forecast widgets for next 7 days
    void updateWeatherInfo(const QString &lat, const QString &lon);
public slots:
    void weatherUpdateRequested();
private slots:
    void onRequestProcessed(QNetworkReply *reply);
    void onEditBtnClicked();
};

#endif // LOCATIONFORECAST_H
