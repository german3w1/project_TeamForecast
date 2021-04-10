#include "editlocationdialog.h"

EditLocationDialog::EditLocationDialog(QWidget* parent, QTabWidget* locations, bool &need_update) : BasicLocationDialog(parent)
{
    setWindowTitle("Редактирование локации");

    auto index = locations->currentIndex();
    label_line->setText(locations->tabText(index));
    label_line->setModified(true);

    auto location = qobject_cast<LocationForecast*>(locations->currentWidget());
    latitude_line->setText(location->getLat());
    longitude_line->setText(location->getLon());

    ok_btn->setText("Изменить");

    if(exec() == QDialog::Accepted) {
        auto lat = latitude_line->text();
        auto lon = longitude_line->text();
        locations->setTabText(index, label_line->text());
        if (lat != location->getLat() || lon != location->getLon()) need_update = true;
        location->setLat(lat);
        location->setLon(lon);
    }
}

