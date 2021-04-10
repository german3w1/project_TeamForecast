#ifndef NEWLOCATIONDIALOG_H
#define NEWLOCATIONDIALOG_H

#include <basiclocationdialog.h>
#include <locationforecast.h>

class NewLocationDialog : public BasicLocationDialog
{
public:
    NewLocationDialog(QWidget* parent, QTabWidget* locations);
};

#endif // NEWLOCATIONDIALOG_H
