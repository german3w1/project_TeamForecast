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
#include <scrollareawrapper.h>
#include <currentwidget.h>
#include <hourlywidget.h>
#include <dailywidget.h>

class LocationForecast : public QFrame
{
    Q_OBJECT
public:
    LocationForecast(QWidget* parent);
    void init(const QString &lat, const QString &lon);
    QString getLat();
    QString getLon();
    void setLat(const QString &lat);
    void setLon(const QString &lon);
private:
    bool previous_update_failed;
    QVBoxLayout *main_layout;
    QHBoxLayout *forecasts_layout;
    QFrame *forecasts_frame;
    QHBoxLayout *control_panel_layout;
    QFrame *control_panel_frame;
    QLabel *last_update_time;
    QLabel *last_update_time_val;
    QLabel *update_err_msg;
    QPushButton *update_btn;
    QNetworkAccessManager *network_manager;
    QLabel* latitude;
    QLabel* longitude;

    CurrentWidget *current_widget;
    HourlyWidget *hourly_widgets[47];
    DailyWidget *daily_widgets[8];

private:
    void updateWeatherInfo(const QString &lat, const QString &lon);
private slots:
    void onRequestProcessed(QNetworkReply *reply);
    void onUpdateBtnClicked();
    void onEditBtnClicked();
};

#endif // LOCATIONFORECAST_H
