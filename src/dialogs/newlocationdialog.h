#ifndef NEWLOCATIONDIALOG_H
#define NEWLOCATIONDIALOG_H

#include <src/dialogs/basiclocationdialog.h>
#include <src/models/locationsmanager.h>
#include <src/views/locationforecast.h>

/**
@brief Modal dialog used for creating new user locations
@details If <b> ok_btn </b> is clicked then creates new location widget
with entered in this dialog label, latitude and longitude.\n
Then adds created widget to <b> locations </b> and switches tab page to it.
*/

class NewLocationDialog : public BasicLocationDialog {
public:
    /**
    @brief Constructs new modal NewLocationDialog
    @param parent Parent for this dialog
    @param locations QTabWidget containing all opened locations
    */
    NewLocationDialog(QWidget* parent,
        LocationsManager* manager,
        QWidget* dimmable_widget = nullptr);
    virtual ~NewLocationDialog();
};

#endif // NEWLOCATIONDIALOG_H
