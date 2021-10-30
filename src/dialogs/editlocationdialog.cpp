#include "dialogs/editlocationdialog.h"

EditLocationDialog::EditLocationDialog(QWidget* parent, LocationModel& location_model, QWidget* dimmable_widget)
    : BasicLocationDialog(parent, dimmable_widget)
{
    title_->setText("Редактирование локации");

    label_line->setText(location_model.label());
    label_line->setModified(true);

    latitude_line->setText(location_model.latitude());
    longitude_line->setText(location_model.longitude());

    ok_btn->setText("Сохранить");
    ok_btn->hide();

    connect(ok_btn,
        &AnimatedButton::clicked,
        this,
        [&]() {
            location_model.setLabel(label_line->text());
            location_model.setGeo(latitude_line->text(),
                longitude_line->text());
            closeDialog();
        });
}

EditLocationDialog::~EditLocationDialog()
{
}
