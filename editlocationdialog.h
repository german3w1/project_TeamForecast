#ifndef EDITLOCATIONDIALOG_H
#define EDITLOCATIONDIALOG_H

#include <basiclocationdialog.h>
#include <locationforecast.h>

class EditLocationDialog : public BasicLocationDialog
{
public:
    EditLocationDialog(QWidget* parent, QTabWidget* locations, bool &need_update);
};

#endif // EDITLOCATIONDIALOG_H
