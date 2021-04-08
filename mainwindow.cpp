#include "mainwindow.h"
#include "locationforecast.h"
#include <newlocationdialog.h>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    //move(QPoint(400,100));
    setMinimumWidth(1100);
    setMinimumHeight(600);
    //setStyleSheet("QWidget {background-color: red}");
    auto main_layout = new QVBoxLayout(this);
    main_layout->setContentsMargins(0,0,0,0);

    locations = new QTabWidget(this);
    locations->setMovable(true);
    locations->tabBar()->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    auto add_new_frame = new QWidget(locations);
    auto add_new_layout = new QVBoxLayout(add_new_frame);
    add_new_layout->setContentsMargins(0, 2, 8, 4);
    auto add_new_btn = new QPushButton(locations);
    add_new_btn->setText("Добавить локацию");
    add_new_btn->setFixedSize(add_new_btn->width() + 48, add_new_btn->height() - 6);
    add_new_btn->setStyleSheet("QPushButton {font: 14px; border: 0px; border-radius: 12px;}"
                               "QPushButton::pressed {background-color: #E0E0E0}");
    connect(add_new_btn, &QPushButton::clicked, this, &MainWindow::newLocationRequest);
    add_new_layout->addWidget(add_new_btn);
    add_new_frame->setLayout(add_new_layout);
    add_new_frame->setFixedHeight(add_new_frame->height());

    locations->setCornerWidget(add_new_frame, Qt::TopRightCorner);
    locations->setTabsClosable(true);
    locations->setStyleSheet(QString("QTabBar::tab {height: %1;}"
                             "QTabBar::close-button {image: url(:/icons/close.png);}"
                             "QTabBar::close-button:hover {image: url(:/icons/close_hover.png);}").arg(add_new_frame->height()));
    connect(locations, &QTabWidget::tabCloseRequested, this, &MainWindow::deleteLocationRequest);
    main_layout->addWidget(locations);

    setLayout(main_layout);
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
