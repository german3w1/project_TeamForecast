#ifndef ROUNDEDMENU_H
#define ROUNDEDMENU_H

#include <QWidget>
#include <QPainter>
#include <QPushButton>
#include <QVBoxLayout>
#include <darkoverlayeffect.h>
#include <dialogs/editlocationdialog.h>
#include <views/locationforecast.h>
#include <QApplication>
#include <QClipboard>
#include <models/locationsmanager.h>

class RoundedMenu : public QWidget
{
    Q_OBJECT
public:
    RoundedMenu(LocationModel *model, LocationsManager *manager, QPoint pos, QWidget *parent);
protected:
    void paintEvent(QPaintEvent *event);
    void focusOutEvent(QFocusEvent *event);
private:
    QPushButton *update_btn;
    QPushButton *delete_btn;
    QPushButton *copy_btn;
    QPushButton *edit_btn;
    LocationModel *model_;
    LocationsManager *manager_;
    LocationForecast *location_forecast_;
private slots:
    void onUpdateBtnClicked() { model_->updateModel(); deleteLater(); }
    void onCopyBtnClicked();
    void onDeleteBtnClicked();
    void onEditBtnClicked();
signals:

};

#endif // ROUNDEDMENU_H
