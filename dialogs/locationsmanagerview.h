#ifndef LOCATIONSMANAGERVIEW_H
#define LOCATIONSMANAGERVIEW_H
#include <QLineEdit>
#include <base/scrollareawrapper.h>
#include <models/locationsmanager.h>
#include <views/locationminiview.h>
#include <dialogs/roundeddialog.h>

class LocationsManagerView : public RoundedDialog
{
    Q_OBJECT
public:
    LocationsManagerView(QWidget *parent, LocationsManager* manager, QWidget *dimmable_widget = nullptr);
    virtual ~LocationsManagerView();
private:
    QLineEdit *search_line;
    QGridLayout *layout;
    ScrollAreaWrapper *locations_list;
    LocationsManager *content_manager;
signals:
    void pickedModel(LocationModel *model);
public slots:
    void onContentChanged();
};

#endif // LOCATIONSMANAGERVIEW_H
