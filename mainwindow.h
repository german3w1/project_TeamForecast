#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QTabWidget>
#include <QTabBar>
#include <QVBoxLayout>
#include <QTimer>
#include <QFile>
#include <QMouseEvent>
#include <QLabel>
#include <QSettings>
#include <QStandardPaths>

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void aboutRequest();
    void newLocationRequest();
    void deleteLocationRequest(int index);
    void changeThemeRequest();
    void updateWeatherRequest();
    void openSettingsRequest();
private:
    QPoint offset;
    bool moving_in_move_area;
    bool dark_theme_enabled;
    QPushButton *settings_btn;
    QPushButton *add_btn;
    QPushButton *collapse_btn;
    QPushButton *close_btn;
    QPushButton *switch_btn;
    QLabel *move_area;
    QTabWidget *locations;
    QTimer *update_timer;
    void setLightTheme();
    void setDarkTheme();
    void restoreLocations();
    void saveLocations(bool only_favorite);
    void restoreAll();
protected:
    void closeEvent(QCloseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
};
#endif // MAINWINDOW_H
