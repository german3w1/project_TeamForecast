#ifndef LOCATIONMINIVIEW_H
#define LOCATIONMINIVIEW_H

#include <QWidget>
#include <QGridLayout>
#include <QStyleOption>
#include <QPainter>
#include <QMouseEvent>
#include <base/animatedwidget.h>
#include <models/locationmodel.h>
#include <models/locationsmanager.h>
#include <roundedmenu.h>
#include <QLabel>
#include <QMenu>

class LocationMiniView : public AnimatedWidget
{
    Q_OBJECT
public:
    explicit LocationMiniView(QWidget *parent, LocationModel* model, LocationsManager *manager);
    LocationModel* model() { return model_; }
private:
    QLabel *name_;
    QLabel *coordinates_;
    QLabel *update_time_;
    QLabel *temp_label_;
    QLabel *temp_value_;
    LocationModel *model_;
    LocationsManager *manager_;
protected:
    virtual void mousePressEvent(QMouseEvent *event);
signals:
    void clicked(LocationModel *model);
private slots:
    void contentUpdated();
};

#endif // LOCATIONMINIVIEW_H
