#include "dialogs/locationsmanagerview.h"
#include <QLabel>

LocationsManagerView* LocationsManagerView::instance_ = nullptr;

LocationsManagerView* LocationsManagerView::create(QWidget* parent, LocationsManager* manager, QWidget* dimmable_widget)
{
    if (instance_ == nullptr) {
        instance_ = new LocationsManagerView(parent, manager, dimmable_widget);
    }
    return instance_;
}

LocationsManagerView::LocationsManagerView(QWidget* parent, LocationsManager* manager, QWidget* dimmable_widget)
    : RoundedDialog(parent, dimmable_widget)
{
    title_->deleteLater();
    //setFocus();
    content_manager = manager;
    connect(content_manager, &LocationsManager::contentChanged,
        this, &LocationsManagerView::onContentChanged);
    layout = new QGridLayout();

    setLayout(layout);
    setStyleSheet("QLineEdit {border-radius: 10px;}");

    search_line = new QLineEdit();
    search_line->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    search_line->setFixedHeight(search_line->sizeHint().height() * 1.5);
    search_line->setAlignment(Qt::AlignCenter);
    search_line->setPlaceholderText("Название, долгота или широта");
    layout->addWidget(search_line, 0, 0, 1, 4);

    locations_list = new ScrollAreaWrapper(this);
    for (auto& each : manager->all()) {
        auto lmv = new LocationMiniView(this, each, content_manager);
        connect(lmv, &LocationMiniView::clicked,
            content_manager->location_view(), &LocationForecast::setModel);
        connect(lmv, &LocationMiniView::clicked,
            this, &LocationsManagerView::closeDialog);
        locations_list->scroll_layout->addWidget(lmv);
    }
    layout->addWidget(locations_list, 1, 0, 15, 4);
}

LocationsManagerView::~LocationsManagerView()
{
    instance_ = nullptr;
}

void LocationsManagerView::onContentChanged()
{
    locations_list->clear();
    for (auto& each : content_manager->all()) {
        auto lmv = new LocationMiniView(this, each, content_manager);
        connect(lmv, &LocationMiniView::clicked,
            content_manager->location_view(), &LocationForecast::setModel);
        connect(lmv, &LocationMiniView::clicked,
            this, &LocationsManagerView::closeDialog);
        locations_list->scroll_layout->addWidget(lmv);
    }
}
