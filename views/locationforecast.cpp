#include "views/locationforecast.h"
#include <dialogs/editlocationdialog.h>

LocationForecast::LocationForecast(QWidget *parent) : QFrame(parent)
{
    setContentsMargins(0,0,0,0);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    auto main_layout = new QVBoxLayout;
    setLayout(main_layout);

    control_panel_frame = new QFrame(this);
    control_panel_frame->setContentsMargins(2,0,2,0);
    auto control_panel_layout = new QHBoxLayout;
    control_panel_frame->setLayout(control_panel_layout);
    main_layout->addWidget(control_panel_frame);
    control_panel_frame->setObjectName("control_panel_frame");

    auto edit = new QPushButton;
    edit->setIcon(QIcon(":/icons/edit"));
    edit->setIconSize(QSize(18, 18));
    edit->setMaximumSize(30, 30);
    connect(edit, &QPushButton::clicked,
            this, &LocationForecast::onEditBtnClicked);
    favorite_checkbox = new QRadioButton;
    favorite_checkbox->setObjectName("favorite_checkbox");
    favorite_checkbox->setChecked(false);
    latitude = new QLabel;
    latitude->setObjectName("val_label");
    longitude = new QLabel;
    longitude->setObjectName("val_label");
    last_update_time = new QLabel("Последнее успешное обновление");
    last_update_time->setObjectName("last_update_time");
    last_update_time_val = new QLabel;
    last_update_time_val->setObjectName("val_label");
    update_btn = new QPushButton("Обновить", control_panel_frame);
    update_btn->setSizePolicy(QSizePolicy::MinimumExpanding,
                              QSizePolicy::MinimumExpanding);
    connect(update_btn, &QPushButton::clicked,
            this, &LocationForecast::weatherUpdateRequested);

    control_panel_layout->addWidget(edit, 1);
    control_panel_layout->addWidget(favorite_checkbox, 1, Qt::AlignCenter);
    control_panel_layout->addWidget(latitude, 1, Qt::AlignCenter);
    control_panel_layout->addWidget(longitude, 1, Qt::AlignCenter);
    control_panel_layout->addWidget(last_update_time, 3, Qt::AlignRight);
    control_panel_layout->addWidget(last_update_time_val, 2, Qt::Alignment(Qt::AlignCenter));
    control_panel_layout->addWidget(update_btn, 1);
    control_panel_frame->setFixedHeight(control_panel_frame->height() + 20);

    forecasts_frame = new QFrame(this);
    forecasts_frame->setContentsMargins(0,0,0,0);
    forecasts_frame->setObjectName("forecast_frame");
    forecasts_frame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    auto forecasts_layout = new QHBoxLayout;
    forecasts_frame->setLayout(forecasts_layout);

    auto current_and_hourly = new ScrollAreaWrapper(this);
    auto current_label = new QLabel("Текущая погода");
    current_label->setObjectName("title_label");
    current_widget = new CurrentWidget;

    auto hourly_label = new QLabel("Почасовой прогноз");
    hourly_label->setObjectName("title_label");
    current_and_hourly->scroll_layout->addWidget(current_label, 0, Qt::Alignment(Qt::AlignHCenter));
    current_and_hourly->scroll_layout->addWidget(current_widget);
    current_and_hourly->scroll_layout->addWidget(hourly_label, 0, Qt::Alignment(Qt::AlignHCenter));
    for (auto i = 0; i < 47; i++) {
        hourly_widgets[i] = new HourlyWidget(this);
        current_and_hourly->scroll_layout->addWidget(hourly_widgets[i]);
    }

    auto daily = new ScrollAreaWrapper(this);
    auto daily_label = new QLabel("Прогноз на неделю");
    daily_label->setObjectName("title_label");
    daily->scroll_layout->addWidget(daily_label, 0, Qt::Alignment(Qt::AlignHCenter));
    for (auto i = 0; i < 7; i++) {
        daily_widgets[i] = new DailyWidget;
        daily->scroll_layout->addWidget(daily_widgets[i]);
    }
    forecasts_layout->addWidget(current_and_hourly);
    forecasts_layout->addWidget(daily);
    main_layout->addWidget(forecasts_frame);
    model_ = nullptr;
}

LocationForecast::LocationForecast
(const QString &lat, const QString &lon, QWidget* parent) : LocationForecast(parent)
{
    latitude->setText(lat);
    longitude->setText(lon);
    setModel(new LocationModel("23", "23", "Africa"));
}

void LocationForecast::setModel(LocationModel *model)
{
    if (model != model_) {
        if (model_) {
            disconnect(model_, &LocationModel::updateFinished,
                    this, &LocationForecast::onUpdateFinished);
            disconnect(model_, &LocationModel::changed,
                    this, &LocationForecast::modelChanged);
            disconnect(model_, &QObject::destroyed,
                    this, &LocationForecast::modelDestroyed);
        }
        if (model) {
            model_ = model;
            connect(model_, &LocationModel::updateFinished,
                    this, &LocationForecast::onUpdateFinished);
            connect(model_, &LocationModel::changed,
                    this, &LocationForecast::modelChanged);
            connect(model_, &QObject::destroyed,
                    this, &LocationForecast::modelDestroyed);
            onUpdateFinished();
        }
    }
}

void LocationForecast::modelDestroyed()
{
    model_ = nullptr;
    emit modelChanged(model_);
    hide();
}

void LocationForecast::onEditBtnClicked()
{
    auto dialog = new EditLocationDialog(parentWidget(), *model_, this);
    dialog->open();
}

void LocationForecast::updateWeatherInfo()
{
    update_btn->setEnabled(false);
    update_btn->setText("Обновление");
    model_->updateModel();
}

void LocationForecast::onUpdateFinished()
{
    current_widget->updateWidgetInfo(model_->current());
    auto hourly_models = model_->hourly();
    for (auto i = 0; i < 47; i++)
        hourly_widgets[i]->updateWidgetInfo(hourly_models[i]);
    auto daily_models = model_->daily();
    for (auto i = 0; i < 7; i++)
        daily_widgets[i]->updateWidgetInfo(daily_models[i]);

    latitude->setText(model_->latitude());
    longitude->setText(model_->longitude());
    last_update_time->setText(model_->updateTime());
    favorite_checkbox->setChecked(model_->isFavourite());

    emit modelChanged(model_);
    update_btn->setEnabled(true);
    update_btn->setText("Обновить");
}

void LocationForecast::onUpdateAborted()
{

}

void LocationForecast::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setBrush(QBrush(AppStyle::backgroundColor(ROLE::SECONDARY, STATE::NORMAL)));
    painter.setPen(Qt::NoPen);
    painter.drawRect(rect());
}

QString LocationForecast::getLat()
{
    return latitude->text();
}

QString LocationForecast::getLon()
{
    return longitude->text();
}


void LocationForecast::setLat(const QString &lat)
{
    latitude->setText(lat);
}

void LocationForecast::setLon(const QString &lon)
{
    longitude->setText(lon);
}

bool LocationForecast::isFavorite() {
    return favorite_checkbox->isChecked();
}

void LocationForecast::setFavorite(bool value)
{
    favorite_checkbox->setChecked(value);
}

void LocationForecast::weatherUpdateRequested()
{
    updateWeatherInfo();
}

