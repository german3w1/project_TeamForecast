#include "src/views/locationminiview.h"

LocationMiniView::LocationMiniView(QWidget* parent, LocationModel* model, LocationsManager* manager)
    : AnimatedWidget(parent)
{
    setRole(ROLE::PRIMARY);
    setRadius(AppStyle::smallestCornerRadius());
    model_ = model;
    manager_ = manager;
    connect(model_, &LocationModel::changed,
        this, &LocationMiniView::contentUpdated);
    connect(model_, &LocationModel::updateFinished,
        this, &LocationMiniView::contentUpdated);
    connect(model_, &QObject::destroyed,
        this, &LocationMiniView::deleteLater);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
    auto view_layout = new QGridLayout();
    setLayout(view_layout);

    name_ = new QLabel(model_->label());
    coordinates_ = new QLabel(model_->latitude() + ", " + model_->longitude());
    update_time_ = new QLabel(model_->updateTime());
    temp_label_ = new QLabel("Температура/Ощущается");
    temp_value_ = new QLabel(model_->current().temperature("temperature") + "/" + model_->current().temperature("reelfeel"));

    view_layout->addWidget(name_, 0, 0, 1, 4);
    view_layout->addWidget(coordinates_, 1, 0, 1, 1);
    view_layout->addWidget(update_time_, 1, 6, 1, 2);
    view_layout->addWidget(temp_label_, 0, 6, 1, 1);
    view_layout->addWidget(temp_value_, 0, 7, 1, 1);
    setStyleSheet("QLabel {font: 12px solid; color: white ;}");
    setFixedHeight(sizeHint().height() * 1.2);
}

void LocationMiniView::mousePressEvent(QMouseEvent* event)
{
    AnimatedWidget::mousePressEvent(event);
    if (event->button() == Qt::RightButton) {
        auto popup_menu = new RoundedMenu(model_, manager_, mapToGlobal(event->pos()), this);
        popup_menu->show();
    } else if (event->button() == Qt::LeftButton) {
        emit clicked(model_);
    }
}

void LocationMiniView::contentUpdated()
{
    name_->setText(model_->label());
    coordinates_->setText(model_->latitude() + ", " + model_->longitude());
    update_time_->setText(model_->updateTime());
    temp_value_->setText(model_->current().temperature("temperature") + "/" + model_->current().temperature("reelfeel"));
}
