#include "aboutdialog.h"
#include <QDebug>

AboutDialog::AboutDialog(QWidget *parent) : QDialog(parent, Qt::FramelessWindowHint)
{
    setContentsMargins(8, 4, 8, 0);
    setMinimumWidth(400);
    setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);

    auto main_layout = new QVBoxLayout;
    setLayout(main_layout);

    auto title = new QLabel("О TeamForecast");
    title->setObjectName("title_label");

    auto logo_frame = new QFrame;
    auto logo_layout = new QHBoxLayout;
    logo_frame->setLayout(logo_layout);

    auto ow_logo = new QLabel;
    ow_logo->setPixmap(QIcon(":/icons/ow_logo_dark").pixmap(241, 92));
    auto qt_logo = new QLabel;
    qt_logo->setPixmap(QIcon(":/icons/qt_logo").pixmap(241, 92));
    logo_layout->addWidget(ow_logo);
    logo_layout->addWidget(qt_logo);

    auto version = new QLabel("v1.8.1");
    version->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    auto author = new QLabel("German Petrin, 2021");
    author->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    auto about = new QLabel("Бесплатный погодный клиент с возможностью\nполучения прогноза погоды по координатам");

    auto details = new QLabel;
    details->setText("<a href=\"https://github.com/german3w1/project_TeamForecast\" style=\"color: black;\" >Подробнее на Github</a>");
    details->setTextFormat(Qt::RichText);
    details->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    details->setOpenExternalLinks(true);

    auto cancel_btn = new QPushButton("Закрыть");
    cancel_btn->setMinimumHeight(cancel_btn->sizeHint().height() * 1.5);
    cancel_btn->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
    connect(cancel_btn, &QPushButton::clicked, this, &QDialog::reject);

    main_layout->addWidget(title);
    main_layout->addWidget(logo_frame, 0);
    main_layout->addWidget(version, 0, Qt::AlignHCenter);
    main_layout->addWidget(author, 0, Qt::AlignHCenter);
    main_layout->addWidget(about);
    main_layout->addWidget(details);
    main_layout->addWidget(cancel_btn);

    exec();
}

AboutDialog::~AboutDialog() {
}
