#ifndef LOCATIONFORECAST_H
#define LOCATIONFORECAST_H

#include <QDebug>
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
#include <QJsonObject>
#include <QJsonArray>
#include <QRadioButton>
#include <scrollareawrapper.h>
#include <currentwidget.h>
#include <hourlywidget.h>
#include <dailywidget.h>

class LocationForecast : public QFrame
{
    Q_OBJECT
public:
    LocationForecast(const QString &lat, const QString &lon, QWidget* parent = 0);
    void setLat(const QString &lat);
    void setLon(const QString &lon);
    QString getLat();
    QString getLon();
    bool isFavorite();
    void setFavorite(bool value);
    void updateWeatherInfo();
private:
    bool previous_update_failed;
    QFrame *forecasts_frame;
    QFrame *control_panel_frame;
    QRadioButton *favorite_checkbox;
    QLabel *last_update_time;
    QLabel *last_update_time_val;
    QLabel *update_err_msg;
    QPushButton *update_btn;
    QNetworkAccessManager *network_manager;
    QLabel* latitude;
    QLabel* longitude;
    CurrentWidget *current_widget;
    HourlyWidget *hourly_widgets[47];
    DailyWidget *daily_widgets[7];
    void updateWeatherInfo(const QString &lat, const QString &lon);
public slots:
    void weatherUpdateRequested();
private slots:
    void onRequestProcessed(QNetworkReply *reply);
    void onEditBtnClicked();
};

#endif // LOCATIONFORECAST_H
