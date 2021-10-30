#ifndef LOCATIONMINIVIEW_H
#define LOCATIONMINIVIEW_H

#include <QGridLayout>
#include <QLabel>
#include <QMenu>
#include <QMouseEvent>
#include <QPainter>
#include <QStyleOption>
#include <QWidget>
#include <src/base/animatedwidget.h>
#include <src/models/locationmodel.h>
#include <src/models/locationsmanager.h>
#include <src/roundedmenu.h>

class LocationMiniView : public AnimatedWidget {
    Q_OBJECT
public:
    explicit LocationMiniView(QWidget* parent, LocationModel* model, LocationsManager* manager);
    LocationModel* model() { return model_; }

private:
    QLabel* name_;
    QLabel* coordinates_;
    QLabel* update_time_;
    QLabel* temp_label_;
    QLabel* temp_value_;
    LocationModel* model_;
    LocationsManager* manager_;

protected:
    virtual void mousePressEvent(QMouseEvent* event);
signals:
    void clicked(LocationModel* model);
private slots:
    void contentUpdated();
};

#endif // LOCATIONMINIVIEW_H
