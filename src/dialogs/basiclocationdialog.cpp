#include "dialogs/basiclocationdialog.h"

BasicLocationDialog::BasicLocationDialog(QWidget* parent, QWidget* dimmable_widget)
    : RoundedDialog(parent, dimmable_widget)
{
    setContentsMargins(8, 0, 8, 0);
    setMinimumWidth(400);
    setMinimumHeight(250);
    auto dialog_layout = new QGridLayout;
    dialog_layout->setSpacing(4);
    setLayout(dialog_layout);

    auto controls_frame = new QFrame;
    controls_frame->setContentsMargins(0, 0, 0, 0);
    auto controls_layout = new QHBoxLayout;
    controls_layout->setSpacing(8);
    controls_frame->setLayout(controls_layout);

    ok_btn = new AnimatedButton("",
        ROLE::SECONDARY,
        AppStyle::mediumCornerRadius());
    ok_btn->setFontParams(10, true);
    ok_btn->setMinimumHeight(ok_btn->sizeHint().height() * 2);

    auto cancel_btn = new AnimatedButton("Отмена",
        ROLE::SECONDARY,
        AppStyle::mediumCornerRadius());
    cancel_btn->setFontParams(10, true);
    cancel_btn->setMinimumHeight(cancel_btn->sizeHint().height() * 2);
    connect(
        cancel_btn, &AnimatedButton::clicked,
        this, &BasicLocationDialog::closeDialog);

    controls_layout->addWidget(ok_btn);
    controls_layout->addWidget(cancel_btn);

    label_line = new QLineEdit; //поле ввода ярлыка(может быть пустым)
    connect(label_line, &QLineEdit::textChanged,
        this, &BasicLocationDialog::onLabelChanged);

    latitude_line = new QLineEdit; //поле ввода широты
    latitude_validator = new QDoubleValidator(-90, 90, 6, latitude_line);
    latitude_validator->setLocale(QLocale::C);
    latitude_line->setValidator(latitude_validator);
    connect(latitude_line, &QLineEdit::textChanged,
        this, &BasicLocationDialog::onLatitudeChanged);

    longitude_line = new QLineEdit; //поле ввода долготы
    longitude_validator = new QDoubleValidator(-180, 180, 6, longitude_line);
    longitude_validator->setLocale(QLocale::C);
    longitude_line->setValidator(longitude_validator);
    connect(longitude_line, &QLineEdit::textChanged,
        this, &BasicLocationDialog::onLongitudeChanged);

    dialog_layout->addWidget(title_, 0, 0, 2, 5);
    dialog_layout->addWidget(new QLabel("Название"), 2, 0, 2, 1);
    dialog_layout->addWidget(label_line, 2, 1, 2, 1);
    dialog_layout->addWidget(new QLabel("Широта"), 4, 0, 2, 1);
    dialog_layout->addWidget(latitude_line, 4, 1, 2, 1);
    dialog_layout->addWidget(new QLabel("Долгота"), 6, 0, 2, 1);
    dialog_layout->addWidget(longitude_line, 6, 1, 2, 1);
    dialog_layout->addWidget(controls_frame, 8, 0, 1, 2);
}

BasicLocationDialog::~BasicLocationDialog()
{
}

void BasicLocationDialog::onLabelChanged(const QString& text)
{
    if (text.size() == 0) {
        label_line->setModified(false);
        ok_btn->hide();
        label_line->setStyleSheet("");
    } else {
        if (latitude_line->hasAcceptableInput() && longitude_line->hasAcceptableInput())
            ok_btn->show();
        label_line->setStyleSheet("border-bottom: 2px solid #00E676;");
    }
}

void BasicLocationDialog::onLatitudeChanged()
{
    if (latitude_line->hasAcceptableInput()) {
        latitude_line->setStyleSheet("border-bottom: 2px solid #00E676;");
        if (longitude_line->hasAcceptableInput()) {
            if (!label_line->isModified())
                label_line->setText(latitude_line->text() + ", " + longitude_line->text());
            ok_btn->show();
        }
    } else {
        if (latitude_line->text().size() != 0)
            latitude_line->setStyleSheet("border-bottom: 2px solid red;");
        else
            latitude_line->setStyleSheet("");
        if (!label_line->isModified())
            label_line->setText("");
        ok_btn->hide();
    }
};

void BasicLocationDialog::onLongitudeChanged()
{
    if (longitude_line->hasAcceptableInput()) {
        longitude_line->setStyleSheet("border-bottom: 2px solid #00E676; ");
        if (latitude_line->hasAcceptableInput()) {
            if (!label_line->isModified())
                label_line->setText(latitude_line->text() + ", " + longitude_line->text());
            ok_btn->show();
        }
    } else {
        if (longitude_line->text().size() != 0)
            longitude_line->setStyleSheet("border-bottom: 2px solid red;");
        else
            longitude_line->setStyleSheet("");
        if (!label_line->isModified())
            label_line->setText("");
        ok_btn->hide();
    }
};
