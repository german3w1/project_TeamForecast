#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <dialogs/roundeddialog.h>

/**
@brief App about modal dialog
@details Here placed title, Qt logo, OpenWeather logo, author name,
year this app version was created,
app version, github page link and some info, also close button
*/

class AboutDialog : public RoundedDialog {
public:
    /**
    @brief Constructs AboutDialog widget
    @param parent Parent for this dialog
    */
    AboutDialog(QWidget* parent, QWidget* dimmable_widget = nullptr);
    virtual ~AboutDialog();
};

#endif // ABOUTDIALOG_H
