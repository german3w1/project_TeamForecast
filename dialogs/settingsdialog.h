#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <dialogs/roundeddialog.h>
#include <QGroupBox>
#include <QLabel>
#include <QRadioButton>
#include <QPushButton>
#include <QSlider>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSettings>

/**
@brief App settings modal dialog
@details This class implements app settings dialog
that allows:\n
Set default app theme modes:\n
    •Light. App sets light theme when starts\n
    •Dark. App sets dark theme when starts\n
    •Current. App always "remember" theme switched before it closes
    and sets that theme when starts\n
Locations save mode:\n
    •None. App saves no locations\n
    •All. Saves all opened locations when app closes\n
    •Only favorite. When app closes it saves only
    locations which marked as favorite\n
Forecasts update interval:\n
    •From 0(disabled) to 24 hours as maximum interval
*/

class SettingsDialog : public RoundedDialog
{
public:
    /**
    @brief Constructs new modal SettingsDialog
    @details In the end of constructor calls loadSettings() to set the actual values of the controls
    @param parent Parent for this dialog
    */
    SettingsDialog(QWidget *parent, QWidget *dimmable_widget = nullptr);
    virtual ~SettingsDialog();
private:
    QRadioButton *theme0; ///< Case dark theme by default enabled
    QRadioButton *theme1; ///< Case light theme by default enabled
    QRadioButton *theme2; ///< Case remember current theme enabled
    QRadioButton *save0; ///< Case save nothing enabled
    QRadioButton *save1; ///< Case save all mode enabled
    QRadioButton *save2; ///< Case save only favorite locations enabled
    QLabel *interval_label; ///< Label showing current value of timer interval slider
    QSlider *interval_slider; ///< Timer interval slider
    void loadSettings();
private slots:
    void onSliderMoved(int value);
    void saveSettings();
};

#endif // SETTINGSDIALOG_H
