#include "dialogs/settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget* parent, QWidget* dimmable_widget)
    : RoundedDialog(parent, dimmable_widget)
{
    setContentsMargins(8, 4, 8, 0);
    setMinimumWidth(400);
    setMinimumHeight(280);
    auto main_layout = new QGridLayout;
    main_layout->setSpacing(0);
    setLayout(main_layout);

    title_->setText("Настройки");

    auto savings_label = new QLabel("Сохранение и восстановление вкладок");
    auto savings_frame = new QFrame;
    savings_frame->setContentsMargins(0, 0, 0, 0);
    auto savings_layout = new QHBoxLayout;
    savings_frame->setLayout(savings_layout);
    save0 = new QRadioButton(tr("Нет"));
    save1 = new QRadioButton(tr("Все"));
    save2 = new QRadioButton(tr("Только избранные"));
    savings_layout->addWidget(save0);
    savings_layout->addWidget(save1);
    savings_layout->addWidget(save2);

    auto theme_label = new QLabel("Тема оформления при запуске");
    auto theme_frame = new QFrame;
    theme_frame->setContentsMargins(0, 0, 0, 0);
    auto theme_layout = new QHBoxLayout;
    theme_frame->setLayout(theme_layout);
    theme0 = new QRadioButton(tr("Тёмная"));
    theme1 = new QRadioButton(tr("Светлая"));
    theme2 = new QRadioButton(tr("Текущая"));
    theme_layout->addWidget(theme0);
    theme_layout->addWidget(theme1);
    theme_layout->addWidget(theme2);

    auto auto_update_frame = new QFrame;
    //auto_update_frame->setContentsMargins(0,0,0,0);
    auto auto_update_layout = new QHBoxLayout;
    auto_update_layout->setContentsMargins(0, 6, 0, 4);
    auto_update_frame->setLayout(auto_update_layout);
    auto auto_update_label = new QLabel("Автообновление");
    interval_slider = new QSlider(Qt::Horizontal);
    interval_slider->setSingleStep(1);
    interval_slider->setPageStep(1);
    interval_slider->setMaximum(24);
    connect(interval_slider, &QSlider::valueChanged, this, &SettingsDialog::onSliderMoved);
    interval_label = new QLabel("выключено");
    auto_update_layout->addWidget(auto_update_label, 1, Qt::AlignVCenter);
    auto_update_layout->addWidget(interval_slider, 2, Qt::AlignVCenter);
    auto_update_layout->addWidget(interval_label, 2, Qt::AlignVCenter);

    auto ok_btn = new AnimatedButton("Сохранить",
        ROLE::SECONDARY,
        AppStyle::mediumCornerRadius());
    ok_btn->setFontParams(10, true);
    ok_btn->setFixedHeight(ok_btn->sizeHint().height() * 2);
    connect(ok_btn, &AnimatedButton::clicked,
        this, &SettingsDialog::saveSettings);

    auto cancel_btn = new AnimatedButton("Закрыть",
        ROLE::SECONDARY,
        AppStyle::mediumCornerRadius());
    cancel_btn->setFontParams(10, true);
    cancel_btn->setFixedHeight(cancel_btn->sizeHint().height() * 2);
    connect(cancel_btn, &AnimatedButton::clicked,
        this, &SettingsDialog::closeDialog);

    main_layout->addWidget(title_, 0, 0, 1, 4);
    main_layout->addWidget(theme_label, 1, 0, 1, 3);
    main_layout->addWidget(theme_frame, 2, 0, 1, 3);
    main_layout->addWidget(savings_label, 3, 0, 1, 3);
    main_layout->addWidget(savings_frame, 4, 0, 1, 3);
    main_layout->addWidget(auto_update_frame, 5, 0, 1, 4);
    main_layout->addWidget(new QLabel, 6, 0, 1, 4);
    main_layout->addWidget(ok_btn, 7, 0, 1, 2);
    main_layout->addWidget(cancel_btn, 7, 2, 1, 2);

    loadSettings();
}

SettingsDialog::~SettingsDialog()
{
}

void SettingsDialog::saveSettings()
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "TeamForecast", "TeamForecast");

    if (theme2->isChecked())
        settings.setValue("remember_theme", true);
    else {
        if (theme0->isChecked())
            settings.setValue("dark_by_default", true);
        else
            settings.setValue("dark_by_default", false);
        settings.setValue("remember_theme", false);
    }

    if (save0->isChecked())
        settings.setValue("save_mode", 0);
    else if (save1->isChecked())
        settings.setValue("save_mode", 1);
    else
        settings.setValue("save_mode", 2);

    if (auto interval = interval_slider->value() * 1000; settings.value("update_interval").toInt() != interval) {
        settings.setValue("update_interval", interval);
        auto location_manager = LocationsManager::getInstance();
        location_manager->setUpdateInterval(interval);
    }

    closeDialog();
}

void SettingsDialog::loadSettings()
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "TeamForecast", "TeamForecast");

    if (settings.value("remember_theme").toBool() == true)
        theme2->setChecked(true);
    else if (int dark_mode = settings.value("dark_by_default").toBool(); dark_mode == true)
        theme0->setChecked(true);
    else
        theme1->setChecked(true);

    if (int save_mode = settings.value("save_mode").toInt(); save_mode == 0)
        save0->setChecked(true);
    else if (save_mode == 1)
        save1->setChecked(true);
    else
        save2->setChecked(true);

    interval_slider->setValue(settings.value("update_interval").toInt());
}

void SettingsDialog::onSliderMoved(int value)
{
    QString new_text;
    if (value == 0)
        new_text = "выключено";
    else if (value == 1)
        new_text = "каждый час";
    else if (auto h = value % 10; 1 < h && h < 5 && !(11 < value && value < 15))
        new_text = QString("каждые %1 часа").arg(value);
    else if (h == 1 && value != 11)
        new_text = QString("каждый %1 час").arg(value);
    else
        new_text = QString("каждые %1 часов").arg(value);

    interval_label->setText(new_text);
}
