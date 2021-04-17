#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QTabWidget>
#include <QTabBar>
#include <QVBoxLayout>

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
private:
    bool dark_theme_enabled;
    QPushButton *add_btn;
    QPushButton *collapse_btn;
    QPushButton *close_btn;
    QPushButton *switch_btn;
    QTabWidget *locations;
    void setLightTheme();
    void setDarkTheme();
};
#endif // MAINWINDOW_H
