#include "dialogs/newlocationdialog.h"

NewLocationDialog::NewLocationDialog(QWidget* parent, LocationsManager* manager, QWidget* dimmable_widget)
    : BasicLocationDialog(parent, dimmable_widget)
{
    title_->setText("Добавление новой локации");

    ok_btn->setText("Добавить");
    ok_btn->hide();
    ok_btn->connect(ok_btn,
        &AnimatedButton::clicked,
        this,
        [=]() {
            auto label = label_line->text();
            auto lat = latitude_line->text();
            auto lon = longitude_line->text();
            manager->add(lat, lon, label);
            closeDialog();
        });
}

NewLocationDialog::~NewLocationDialog()
{
}
