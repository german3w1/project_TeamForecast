#include "mainwindow.h"
#include "locationforecast.h"
#include <newlocationdialog.h>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    setMinimumWidth(1100);
    setMinimumHeight(600);
    auto main_layout = new QVBoxLayout;
    main_layout->setContentsMargins(0,0,0,0);
    setLayout(main_layout);

    locations = new QTabWidget;
    locations->setMovable(true);
    locations->setTabsClosable(true);
    locations->tabBar()->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    connect(locations, &QTabWidget::tabCloseRequested, this, &MainWindow::deleteLocationRequest);

    auto add_new_frame = new QWidget(locations);
    auto add_new_layout = new QVBoxLayout;
    add_new_layout->setContentsMargins(0, 2, 8, 4);
    add_new_frame->setLayout(add_new_layout);

    auto add_new_btn = new QPushButton(locations);
    add_new_btn->setText("Добавить локацию");
    add_new_btn->setFixedSize(add_new_btn->width() + 48, add_new_btn->height() - 6);
    add_new_btn->setStyleSheet("QPushButton {font: 14px; border: 0px; border-radius: 12px;}"
                               "QPushButton::pressed {background-color: #E0E0E0}");
    connect(add_new_btn, &QPushButton::clicked, this, &MainWindow::newLocationRequest);
    add_new_frame->setFixedHeight(add_new_frame->height());
    add_new_layout->addWidget(add_new_btn);

    locations->setCornerWidget(add_new_frame, Qt::TopRightCorner);
    locations->setStyleSheet(QString("QTabBar::tab {height: %1;}"
                             "QTabBar::close-button {image: url(:/icons/close);}"
                             "QTabBar::close-button:hover {image: url(:/icons/close_hover);}").arg(add_new_frame->height()));

    main_layout->addWidget(locations);
}

MainWindow::~MainWindow()
{

}

void MainWindow::newLocationRequest(){
   NewLocationDialog(this, locations);
}

void MainWindow::deleteLocationRequest(int index){
    delete locations->widget(index);
}
