#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

/**
@brief App about modal dialog
@details Here placed title, Qt logo, OpenWeather logo, author name,
year this app version was created,
app version, github page link and some info, also close button
*/

class AboutDialog : public QDialog
{
    Q_OBJECT
public:
    /**
    @brief Constructs AboutDialog widget
    @param parent Parent for this dialog
    */
    AboutDialog(QWidget *parent);
    ~AboutDialog();
};

#endif // ABOUTDIALOG_H
