#ifndef BASICLOCATIONDIALOG_H
#define BASICLOCATIONDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QDoubleValidator>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <darkoverlayeffect.h>

class BasicLocationDialog : public QDialog
{
    Q_OBJECT
protected:
    BasicLocationDialog(QWidget *parent);
    QLabel *title;
    QLineEdit* label_line;
    QLineEdit* latitude_line;
    QLineEdit* longitude_line;
    QPushButton* ok_btn;
private:
    QDoubleValidator *latitude_validator;
    QDoubleValidator *longitude_validator;
private slots:
    void onLabelChanged(const QString &text);
    void onLatitudeChanged();
    void onLongitudeChanged();
};

#endif // BASICLOCATIONDIALOG_H
