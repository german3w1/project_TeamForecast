#include "src/models/locationmodel.h"

LocationModel::LocationModel()
{
    current_model = CurrentModel();
    hourly_models = QList<HourlyModel>(47);
    daily_models = QList<DailyModel>(7);
}

LocationModel::LocationModel(const QString& latitude, const QString& longitude, const QString& label)
    : LocationModel()
{
    latitude_ = latitude;
    longitude_ = longitude;
    label_ = label;
}

QJsonDocument LocationModel::asJsonDocument()
{
    QJsonObject document;

    document.insert("label", label_);
    document.insert("latitude", latitude_);
    document.insert("longitude", longitude_);

    document.insert("current", current_model.asJsonObject());

    QJsonArray hourly_part;
    for (auto& each : hourly_models)
        hourly_part.push_back(each.asJsonObject());
    document.insert("hourly", hourly_part);

    QJsonArray daily_part;
    for (auto& each : daily_models)
        daily_part.push_back(each.asJsonObject());
    document.insert("daily", daily_part);

    return QJsonDocument(document);
}

void LocationModel::updateModel()
{
    network_manager = new QNetworkAccessManager(this);
    connect(network_manager, &QNetworkAccessManager::finished,
        this, &LocationModel::onRequestProcessed);
    QString api_key = "3e69eacb46ce8074001a5562dfb9e38a";
    QString url = "https://api.openweathermap.org/data/2.5/onecall?lat=%1&lon=%2&exclude=minutely,alerts&units=metric&appid=%3";
    url = url.arg(latitude_, longitude_, api_key);
    network_manager->get(QNetworkRequest(QUrl(url)));
}

void LocationModel::setLatitude(QString latitude)
{
    auto temp = latitude_;
    latitude_ = latitude;
    if (temp != latitude)
        emit changed(this);
}

void LocationModel::setLongitude(QString longitude)
{
    auto temp = longitude_;
    longitude_ = longitude;
    if (temp != longitude)
        emit changed(this);
}

void LocationModel::setLabel(QString value)
{
    auto temp = label_;
    label_ = value;
    if (temp != value)
        emit changed(this);
}

void LocationModel::setGeo(const QString& latitude, const QString& longitude)
{
    auto old_latitude = latitude_;
    auto old_longitude = longitude_;

    latitude_ = latitude;
    longitude_ = longitude;
    if (old_latitude != latitude || old_longitude != longitude)
        emit changed(this);
}

void LocationModel::onRequestProcessed(QNetworkReply* reply)
{

    if (!reply->error()) {
        QJsonDocument json_answer = QJsonDocument::fromJson(reply->readAll());
        QVariantMap new_data = json_answer.toVariant().toMap();
        offset = new_data["timezone_offset"].toInt();
        auto current_dataset = new_data["current"].toMap();
        QDateTime today = QDateTime::fromSecsSinceEpoch(current_dataset["dt"].toLongLong(), Qt::OffsetFromUTC, offset);
        QVariantList hourly_dataset = new_data["hourly"].toList();
        QVariantList daily_dataset = new_data["daily"].toList();

        current_model.updateModel(current_dataset, offset);
        for (auto i = 0; i < 47; i++)
            hourly_models[i].updateModel(hourly_dataset[i + 1].toMap(), today, offset);
        for (auto i = 0; i < 7; i++)
            daily_models[i].updateModel(daily_dataset[i + 1].toMap(), offset);

        latitude_ = new_data["lat"].toString();
        longitude_ = new_data["lon"].toString();
        update_time = QDateTime::currentDateTime();

        emit updateFinished();
    } else {
        emit updateAborted();
    }

    connect(reply, &QNetworkReply::destroyed,
        network_manager, &QNetworkAccessManager::deleteLater);
    reply->deleteLater();
}
