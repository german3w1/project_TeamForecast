#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
    void newLocationRequest();
    void deleteLocationRequest(int index);
private:
    QTabWidget *locations;
};
#endif // MAINWINDOW_H
