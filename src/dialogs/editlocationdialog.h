#ifndef EDITLOCATIONDIALOG_H
#define EDITLOCATIONDIALOG_H

#include <src/dialogs/basiclocationdialog.h>
#include <src/views/locationforecast.h>

/**
@brief Modal dialog used for editing data of the location widget from which it was called
@details If ok_btn is clicked then edits this location widget
with entered in this dialog label, latitude and longitude.\n
If need_update was switched to true (latitude or longitude were changed) after
this dialog is opened, then location widget with edited data updates after dialog closes
*/

class EditLocationDialog : public BasicLocationDialog {
public:
    /**
    @brief Constructs new modal EditLocationDialog
    @param parent Parent for this dialog
    @param locations QTabWidget containing all opened locations
    */
    EditLocationDialog(QWidget* parent,
        LocationModel& location_model,
        QWidget* dimmable_widget = nullptr);
    virtual ~EditLocationDialog();
};

#endif // EDITLOCATIONDIALOG_H
