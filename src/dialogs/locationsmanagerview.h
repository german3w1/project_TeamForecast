#ifndef LOCATIONSMANAGERVIEW_H
#define LOCATIONSMANAGERVIEW_H
#include <QLineEdit>
#include <src/base/scrollareawrapper.h>
#include <src/dialogs/roundeddialog.h>
#include <src/models/locationsmanager.h>
#include <src/views/locationminiview.h>

class LocationsManagerView : public RoundedDialog {
    Q_OBJECT
public:
    static LocationsManagerView* create(QWidget* parent, LocationsManager* manager,
        QWidget* dimmable_widget = nullptr);
    virtual ~LocationsManagerView();

private:
    LocationsManagerView(QWidget* parent, LocationsManager* manager,
        QWidget* dimmable_widget = nullptr);
    static LocationsManagerView* instance_;
    QLineEdit* search_line;
    QGridLayout* layout;
    ScrollAreaWrapper* locations_list;
    LocationsManager* content_manager;
signals:
    void pickedModel(LocationModel* model);
public slots:
    void onContentChanged();
};

#endif // LOCATIONSMANAGERVIEW_H
