#include "editlocationdialog.h"

EditLocationDialog::EditLocationDialog(QWidget* parent, QTabWidget* locations, bool &need_update) : QDialog(parent)
{
    setWindowTitle("Редактирование локации");
    setContentsMargins(8, 4, 8, 0);
    setMinimumWidth(400);
    setStyleSheet("QLabel {font: bold 12px; color: #757575; text-align: center; background: none;}"
                  "QLineEdit {selection-background-color: #E0E0E0; selection-color: black; border: 0px; border-radius: 6px; }"
                  "QPushButton::pressed {background-color: #E0E0E0}");

    auto controls_frame = new QFrame(this);
    controls_frame->setStyleSheet("QFrame {background: none;}");
    controls_frame->setContentsMargins(0,0,0,0);
    auto controls_layout = new QHBoxLayout(controls_frame);
    controls_layout->setSpacing(8);

    ok_btn = new QPushButton("Изменить", controls_frame);
    ok_btn->setMinimumHeight(ok_btn->height() + 2);
    ok_btn->setStyleSheet("QPushButton {font: bold 14px; color: #1E88E5; border: 0px; border-radius: 12px;}");
    connect(ok_btn, &QPushButton::clicked, this, &QDialog::accept);

    auto cancel_btn = new QPushButton("Отмена", controls_frame);
    cancel_btn->setMinimumHeight(cancel_btn->height() + 2);
    cancel_btn->setStyleSheet("QPushButton {font: bold 14px; color: #DD2C00; border: 0px; border-radius: 12px;}");
    connect(cancel_btn, &QPushButton::clicked, this, &QDialog::reject);

    controls_layout->addWidget(ok_btn);
    controls_layout->addWidget(cancel_btn);
    controls_frame->setLayout(controls_layout);

    auto index = locations->currentIndex();

    label_line = new QLineEdit(locations->tabText(index), this);
    label_line->setModified(true);
    connect(label_line, &QLineEdit::textChanged, this, &EditLocationDialog::onLabelChanged);

    auto location = qobject_cast<LocationForecast*>(locations->currentWidget());

    latitude_line = new QLineEdit(location->getLat(), this);  //поле ввода широты
    latitude_validator = new QDoubleValidator(-90,90,6,latitude_line);
    latitude_validator->setLocale(QLocale::C);
    latitude_line->setValidator(latitude_validator);
    connect(latitude_line, &QLineEdit::textEdited, this, &EditLocationDialog::onLatitudeChanged);

    longitude_line = new QLineEdit(location->getLon(), this); //поле ввода долготы
    longitude_validator = new QDoubleValidator(-180,180,6,longitude_line);
    longitude_validator->setLocale(QLocale::C);
    longitude_line->setValidator(longitude_validator);
    connect(longitude_line, &QLineEdit::textEdited, this, &EditLocationDialog::onLongitudeChanged);

    auto dialog_layout = new QVBoxLayout(this);
    dialog_layout->setSpacing(1);

    dialog_layout->addWidget(new QLabel("Название локации", this));
    dialog_layout->addWidget(label_line);

    dialog_layout->addWidget(new QLabel("Широта", this));
    dialog_layout->addWidget(latitude_line);
    lat_error = new QLabel("Неверный ввод", this);
    auto error_size_policy = QSizePolicy(lat_error->sizePolicy());
    error_size_policy.setRetainSizeWhenHidden(true);
    lat_error->setSizePolicy(error_size_policy);
    lat_error->setStyleSheet("QLabel {font: 12px; color: #DD2C00;}");
    dialog_layout->addWidget(lat_error);
    lat_error->hide();

    dialog_layout->addWidget(new QLabel("Долгота", this));
    dialog_layout->addWidget(longitude_line);
    lon_error = new QLabel("Неверный ввод", this);
    lon_error->setSizePolicy(error_size_policy);
    lon_error->setStyleSheet("QLabel {font: 12px; color: #DD2C00;}");
    dialog_layout->addWidget(lon_error);
    lon_error->hide();

    dialog_layout->addWidget(controls_frame);
    setLayout(dialog_layout);

    if(exec() == QDialog::Accepted) {
        auto lat = latitude_line->text();
        auto lon = longitude_line->text();
        locations->setTabText(index, label_line->text());
        if (lat != location->getLat() || lon != location->getLon()) need_update = true;
        location->setLat(lat);
        location->setLon(lon);

    }

}

void EditLocationDialog::onLabelChanged(const QString &text){
    if (text.size() == 0) {
        label_line->setModified(false);
        ok_btn->hide();
    }
    else if (latitude_line->hasAcceptableInput() && longitude_line->hasAcceptableInput())
        ok_btn->show();
}

void EditLocationDialog::onLatitudeChanged(){
    if (latitude_line->hasAcceptableInput()){
        lat_error->hide();
        if (longitude_line->hasAcceptableInput()) {
            if (!label_line->isModified())
                label_line->setText(latitude_line->text() + ", " + longitude_line->text());
            ok_btn->show();
        }
    }
    else {
        if (latitude_line->text().size() != 0) lat_error->show();
        else lat_error->hide();
        if (!label_line->isModified())  label_line->setText("");
        ok_btn->hide();
    }
};

void EditLocationDialog::onLongitudeChanged(){
    if (longitude_line->hasAcceptableInput()){
        lon_error->hide();
        if (latitude_line->hasAcceptableInput()) {
            if (!label_line->isModified())
                label_line->setText(latitude_line->text() + ", " + longitude_line->text());
            ok_btn->show();
        }
    }
    else {
        if (longitude_line->text().size() != 0) lon_error->show();
        else lon_error->hide();
        if (!label_line->isModified()) label_line->setText("");
        ok_btn->hide();
    }
};
