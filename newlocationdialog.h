#ifndef NEWLOCATIONDIALOG_H
#define NEWLOCATIONDIALOG_H

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

class NewLocationDialog : public QDialog
{
public:
    NewLocationDialog(QWidget* parent, QTabWidget* locations);

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

#endif // NEWLOCATIONDIALOG_H
