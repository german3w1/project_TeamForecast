#ifndef EDITLOCATIONDIALOG_H
#define EDITLOCATIONDIALOG_H

#include <QDialog>
#include <QWidget>
#include <QTabWidget>
#include <QLineEdit>
#include <QDoubleValidator>
#include <QVBoxLayout>
#include <QFrame>
#include <QPushButton>
#include <QString>
#include <QLabel>
#include <locationforecast.h>

class EditLocationDialog : public QDialog
{
public:
    EditLocationDialog(QWidget* parent, QTabWidget* locations, bool &need_update);

private:
    QLineEdit* label_line;
    QLineEdit* latitude_line;
    QDoubleValidator *latitude_validator;
    QLabel* lat_error;
    QLineEdit* longitude_line;
    QDoubleValidator *longitude_validator;
    QLabel* lon_error;
    QPushButton* ok_btn;

private slots:
    void onLabelChanged(const QString &text);
    void onLatitudeChanged();
    void onLongitudeChanged();
};

#endif // EDITLOCATIONDIALOG_H
