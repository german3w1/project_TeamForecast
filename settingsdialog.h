#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QGroupBox>
#include <QLabel>
#include <QRadioButton>
#include <QPushButton>
#include <QSlider>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSettings>

class SettingsDialog : public QDialog
{
public:
    SettingsDialog(QWidget *parent);
private:
    QRadioButton *theme0;
    QRadioButton *theme1;
    QRadioButton *theme2;
    QRadioButton *save0;
    QRadioButton *save1;
    QRadioButton *save2;
    QLabel *interval_label;
    QSlider *interval_slider;
    void loadSettings();
private slots:
    void onSliderMoved(int value);
};

#endif // SETTINGSDIALOG_H
