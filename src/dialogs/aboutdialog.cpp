#include "src/dialogs/aboutdialog.h"
#include <QApplication>
#include <QDebug>

AboutDialog::AboutDialog(QWidget* parent, QWidget* dimmable_widget)
    : RoundedDialog(parent, dimmable_widget)
{
    // setContentsMargins(8, 4, 8, 0);
    //setMinimumWidth(400);
    // setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);
    auto main_layout = new QVBoxLayout;
    setLayout(main_layout);

    title_->setText("О TeamForecast");

    auto logo_frame = new QFrame;
    auto logo_layout = new QHBoxLayout;
    logo_frame->setLayout(logo_layout);

    auto ow_logo = new QLabel;
    ow_logo->setPixmap(QIcon(":/icons/ow_logo_dark").pixmap(241, 92));
    auto qt_logo = new QLabel;
    qt_logo->setPixmap(QIcon(":/icons/qt_logo").pixmap(241, 92));
    logo_layout->addWidget(ow_logo);
    logo_layout->addWidget(qt_logo);

    auto version = new QLabel("v2.0.4");
    version->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    auto author = new QLabel("German Petrin, 2021");
    author->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    auto about = new QLabel("Бесплатный погодный клиент с возможностью"
                            "\nполучения прогноза погоды по координатам");

    auto details = new QLabel;
    details->setText(QString("<a href=\"https://github.com/german3w1/project_TeamForecast\" "
                             "style=\"color: %1;\" >Подробнее на Github</a>")
                         .arg(AppStyle::textPrimaryColor().name()));
    details->setTextFormat(Qt::RichText);
    details->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    details->setOpenExternalLinks(true);

    auto cancel_btn = new AnimatedButton("Закрыть", ROLE::SECONDARY, AppStyle::mediumCornerRadius());
    cancel_btn->setMinimumHeight(cancel_btn->sizeHint().height() * 2);
    cancel_btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    cancel_btn->setFontParams(10, true);
    connect(
        cancel_btn, &AnimatedButton::clicked,
        this, &AboutDialog::closeDialog);

    main_layout->addWidget(title_);
    main_layout->addWidget(logo_frame, 0);
    main_layout->addWidget(version, 0, Qt::AlignHCenter);
    main_layout->addWidget(author, 0, Qt::AlignHCenter);
    main_layout->addWidget(about);
    main_layout->addWidget(details);
    main_layout->addWidget(cancel_btn);
}

AboutDialog::~AboutDialog()
{
}
