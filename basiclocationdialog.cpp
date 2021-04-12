#include "basiclocationdialog.h"
#include <QGraphicsDropShadowEffect>

BasicLocationDialog::BasicLocationDialog(QWidget *parent) : QDialog(parent)
{
    setContentsMargins(8, 4, 8, 0);
    setMinimumWidth(400);
    setStyleSheet("QLabel {font: bold 12px; color: #757575; text-align: center;}"
                  "QLineEdit {selection-background-color: #E0E0E0; selection-color: black; border: 0px; border-radius: 6px; }"
                  "QPushButton::pressed {background-color: #E0E0E0}");
    setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Minimum);
    auto dialog_layout = new QVBoxLayout;
    dialog_layout->setSpacing(1);
    setLayout(dialog_layout);

    auto controls_frame = new QFrame;
    controls_frame->setContentsMargins(0,0,0,0);
    auto controls_layout = new QHBoxLayout;
    controls_layout->setSpacing(8);
    controls_frame->setLayout(controls_layout);

    ok_btn = new QPushButton;
    ok_btn->setMinimumHeight(ok_btn->sizeHint().height() * 1.5);
    ok_btn->setStyleSheet("QPushButton {font: bold 14px; color: #1E88E5; border: 0px; border-radius: 12px;}");
    ok_btn->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
    connect(ok_btn, &QPushButton::clicked, this, &QDialog::accept);

    auto cancel_btn = new QPushButton("Отмена");
    cancel_btn->setMinimumHeight(cancel_btn->sizeHint().height() * 1.5);
    cancel_btn->setStyleSheet("QPushButton {font: bold 14px; color: #DD2C00; border: 0px; border-radius: 12px;}");
    cancel_btn->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
    connect(cancel_btn, &QPushButton::clicked, this, &QDialog::reject);

    controls_layout->addWidget(ok_btn);
    controls_layout->addWidget(cancel_btn);

    label_line = new QLineEdit; //поле ввода ярлыка(может быть пустым)
    connect(label_line, &QLineEdit::textChanged, this, &BasicLocationDialog::onLabelChanged);

    latitude_line = new QLineEdit;  //поле ввода широты
    latitude_validator = new QDoubleValidator(-90,90,6,latitude_line);
    latitude_validator->setLocale(QLocale::C);
    latitude_line->setValidator(latitude_validator);
    connect(latitude_line, &QLineEdit::textEdited, this, &BasicLocationDialog::onLatitudeChanged);

    longitude_line = new QLineEdit; //поле ввода долготы
    longitude_validator = new QDoubleValidator(-180,180,6,longitude_line);
    longitude_validator->setLocale(QLocale::C);
    longitude_line->setValidator(longitude_validator);
    connect(longitude_line, &QLineEdit::textEdited, this, &BasicLocationDialog::onLongitudeChanged);

    lat_error = new QLabel("Неверный ввод");
    auto error_size_policy = QSizePolicy(lat_error->sizePolicy());
    error_size_policy.setRetainSizeWhenHidden(true);
    lat_error->setSizePolicy(error_size_policy);
    lat_error->setStyleSheet("QLabel {font: 12px; color: #DD2C00;}");
    lat_error->hide();

    lon_error = new QLabel("Неверный ввод");
    lon_error->setSizePolicy(error_size_policy);
    lon_error->setStyleSheet("QLabel {font: 12px; color: #DD2C00;}");
    lon_error->hide();

    dialog_layout->addWidget(new QLabel("Название локации"));
    dialog_layout->addWidget(label_line);
    dialog_layout->addWidget(new QLabel("Широта"));
    dialog_layout->addWidget(latitude_line);
    dialog_layout->addWidget(lat_error);
    dialog_layout->addWidget(new QLabel("Долгота"));
    dialog_layout->addWidget(longitude_line);
    dialog_layout->addWidget(lon_error);
    dialog_layout->addWidget(controls_frame);

}

void BasicLocationDialog::onLabelChanged(const QString &text){
    if (text.size() == 0) {
        label_line->setModified(false);
        ok_btn->hide();
    }
    else if (latitude_line->hasAcceptableInput() && longitude_line->hasAcceptableInput())
        ok_btn->show();
}

void BasicLocationDialog::onLatitudeChanged(){
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

void BasicLocationDialog::onLongitudeChanged(){
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
