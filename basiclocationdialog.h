#ifndef BASICLOCATIONDIALOG_H
#define BASICLOCATIONDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QDoubleValidator>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

class BasicLocationDialog : public QDialog
{
public:
    BasicLocationDialog(QWidget *parent);
protected:
    QLineEdit* label_line;
    QLineEdit* latitude_line;
    QLineEdit* longitude_line;
    QPushButton* ok_btn;
private:
    QDoubleValidator *latitude_validator;
    QLabel* lat_error;
    QDoubleValidator *longitude_validator;
    QLabel* lon_error;
private slots:
    void onLabelChanged(const QString &text);
    void onLatitudeChanged();
    void onLongitudeChanged();
};

#endif // BASICLOCATIONDIALOG_H
