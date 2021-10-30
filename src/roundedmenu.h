#ifndef ROUNDEDMENU_H
#define ROUNDEDMENU_H

#include <QApplication>
#include <QClipboard>
#include <QPainter>
#include <QVBoxLayout>
#include <QWidget>
#include <base/animatedbutton.h>
#include <darkoverlayeffect.h>
#include <dialogs/editlocationdialog.h>
#include <models/locationsmanager.h>
#include <views/locationforecast.h>

class RoundedMenu : public QWidget {
    Q_OBJECT
public:
    RoundedMenu(LocationModel* model, LocationsManager* manager, QPoint pos, QWidget* parent);

protected:
    void paintEvent(QPaintEvent* event);
    void focusOutEvent(QFocusEvent* event);

private:
    AnimatedButton* update_btn;
    AnimatedButton* delete_btn;
    AnimatedButton* copy_btn;
    AnimatedButton* edit_btn;
    LocationModel* model_;
    LocationsManager* manager_;
    LocationForecast* location_forecast_;
private slots:
    void onUpdateBtnClicked()
    {
        model_->updateModel();
        deleteLater();
    }
    void onCopyBtnClicked();
    void onDeleteBtnClicked();
    void onEditBtnClicked();
signals:
};

#endif // ROUNDEDMENU_H
