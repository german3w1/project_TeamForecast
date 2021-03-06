#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "views/locationforecast.h"
#include <QApplication>
#include <QFile>
#include <QJsonArray>
#include <QLabel>
#include <QMouseEvent>
#include <QPushButton>
#include <QSettings>
#include <QStandardPaths>
#include <QTabBar>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QWidget>
#include <base/appstyle.h>
#include <darkoverlayeffect.h>
#include <dialogs/aboutdialog.h>
#include <dialogs/locationsmanagerview.h>
#include <dialogs/newlocationdialog.h>
#include <dialogs/settingsdialog.h>
#include <hintwidget.h>
#include <models/locationmodel.h>
#include <views/locationforecast.h>

/**
@brief Main application window
@details Contains QTabWidget locations which
stores user location widgets, implements an abillity to move
app window by overriding QWidget events,
contains buttons opening AboutDialog, NewLocationDialog,
SettingsDialog, collapsing and closing the app and switching app global theme
*/

class MainWindow : public QWidget {
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
    LocationForecast* location_view() { return location_forecast; }
private slots:
    void onLocationModelChanged(LocationModel* model);
    void openAboutDialog();
    void openSettingsDialog();
    void openNewLocationDialog();
    void openLocationManager();

private:
    QPoint offset;
    bool moving_in_move_area; ///<  Property indicates that user pressed move_area
    bool dark_theme_enabled;
    HintWidget* hint_widget_;
    QFrame* control_frame;
    QPushButton* settings_btn; ///< Open settings button
    QPushButton* add_btn; ///< Add new location button
    QPushButton* collapse_btn; ///< App collapse button
    QPushButton* close_btn; ///< Close app button
    QPushButton* switch_btn; ///< Switch app theme button
    AnimatedButton* locations_btn;
    QLabel* move_area; ///< An area that you can pull to move the application window
    QLabel* hello_world;
    LocationsManager* locations_manager;
    LocationsManagerView* location_manager_view;
    LocationForecast* location_forecast;
    void openDialog(RoundedDialog* dialog);
    /**
    @brief Set app theme to light
    @note All buttons and layouts of mainwindow must be created until calling this function
    */
    void setLightTheme();
    /**
    @brief Set app theme to dark
    @note All buttons and layouts of mainwindow must be created until calling this function
    */
    void setDarkTheme();
    /**
    @brief Restore all saved locations
    @details Load location_list.json and and creates locations with the data listed in it
    */
    void restoreLocations();
    /**
    @brief Save locations
    @details If only_favorite is true - saves only locations marked as favorite.\n
    Otherwise saves all opened locations.\n
    If there is no locations - saves empty json.\n
    Json layout:\n
    [\n
        {
        "is_favorite": value,
        "lat": value,
        "lon": value,
        "name": value
        }, \n
        ...,\n
        {
        "is_favorite": value,
        "lat": value,
        "lon": value,
        "name": value
        }\n
    ]\n
    */
    void saveLocations(bool only_favorite);
    /**
    @brief Restore all saved app data
    @details If save_mode was non-zero - calling restoreLocations().\n
    If dark_by_default is true when calls setDarkTheme(), otherwise calls setLightTheme().
    */
    void restoreAll();

protected:
    /**
    @brief Overrided QWidget::closeEvent
    @details Here app saves locations if save_mode != 0
    remembers its theme if remember_theme is true
    and closes
    */
    void closeEvent(QCloseEvent* event);
    /**
    @brief Overrided QWidget::mousePressEvent
    @details This overriding is needed to detect if user
    pressed mouse left button in move_area rectangle\n
    If it is true then sets moving_in_move_area = true
    */
    void mousePressEvent(QMouseEvent* event);
    /**
    @brief Overrided QWidget::mouseMoveEvent
    @details If moving_in_move_area is true then
    move the application window behind the cursor
    until mouse left button is released
    */
    void mouseMoveEvent(QMouseEvent* event);
    /**
    @brief Overrided QWidget::mouseReleaseEvent
    @details When mouse left button is released sets moving_in_move_area = false
    and the application window stops moving behind the cursor
    */
    void mouseReleaseEvent(QMouseEvent* event);

    virtual void paintEvent(QPaintEvent* event);
};
#endif // MAINWINDOW_H
