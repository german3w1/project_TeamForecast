#include "newlocationdialog.h"

NewLocationDialog::NewLocationDialog(QWidget* parent, QTabWidget* locations) : BasicLocationDialog(parent)
{
    parent->setGraphicsEffect(new DarkOverlayEffect);
    title->setText("Добавление новой локации");

    ok_btn->setText("Добавить");
    ok_btn->hide();

    if(exec() == QDialog::Accepted) {
        delete parent->graphicsEffect();
        auto label = label_line->text();
        auto lat = latitude_line->text();
        auto lon = longitude_line->text();
        auto new_location = new LocationForecast(locations);
        locations->addTab(new_location, label);
        locations->setCurrentIndex(locations->count() - 1);
        new_location->init(lat, lon);
    }
    else {
        delete parent->graphicsEffect();
    }
}
