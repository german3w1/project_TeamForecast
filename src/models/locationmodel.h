#ifndef LOCATIONMODEL_H
#define LOCATIONMODEL_H
#include <src/models/currentmodel.h>
#include <src/models/hourlymodel.h>
#include <src/models/dailymodel.h>
#include <QList>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonArray>

class LocationModel : public QObject
{
    Q_OBJECT
public:
    LocationModel();
    LocationModel(const QString &lat_value, const QString &lon_value, const QString &name_value);
    QJsonDocument asJsonDocument();
    void updateModel();
    void setFavourite(bool value) { favourite = value; }
    void setLatitude(QString value);
    void setLongitude(QString value);
    void setLabel(QString value);
    void setGeo(const QString &latitude, const QString &longitude);
    QString updateTime()  { return QLocale::system().toString(update_time); }
    QString latitude()    { return latitude_; }
    QString longitude()   { return longitude_; }
    QString label()       { return label_; }
    bool isFavourite()     { return favourite;}
    const auto& current() const { return current_model; }
    const auto& hourly()  const { return hourly_models; }
    const auto& daily()   const { return daily_models; }
private:
    QString label_;
    QString latitude_;
    QString longitude_;
    bool favourite;
    QDateTime update_time;
    int offset;
    CurrentModel current_model;
    QList<HourlyModel> hourly_models;
    QList<DailyModel> daily_models;
    QNetworkAccessManager *network_manager;
private slots:
    void onRequestProcessed(QNetworkReply *reply);
signals:
    void updateFinished();
    void updateAborted();
    void changed(LocationModel *model);
};

#endif // LOCATIONMODEL_H
