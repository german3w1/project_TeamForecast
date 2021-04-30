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

/**
@brief Basic modal dialog for add/edit location dialogs
@details Contains three input fields(location label, latitude and longitude), title and two control buttons.\n
Sets up latitude_validator for latitude_line
and longitude_validator for longitude_line.\n
All user input validation works using QDoubleValidators and logic implemented in QLineEdit::textChanged slots
*/

class BasicLocationDialog : public QDialog
{
    Q_OBJECT
protected:
    /**
    @brief Constructs BasicLocaitonDialog
    @param parent Parent for this widget
    */
    BasicLocationDialog(QWidget *parent);
    QLabel *title; ///< Dialog title label
    QLineEdit* label_line; ///< Field for entering the name of the location
    QLineEdit* latitude_line; ///< Field for entering the latitude of the location
    QLineEdit* longitude_line; ///< Field for entering the longitude of the location
    QPushButton* ok_btn; ///< Button allowing to add/save location
private:
    QDoubleValidator *latitude_validator; ///< latitude input validator that should accept only numbers in range[-90; 90]
    QDoubleValidator *longitude_validator; ///< longitude input validator that should accept only numbers in range[-180; 180]
private slots:
    /**
    @brief Called when user typed/edited location label or when it was
    automatically filled with latitude and longitude values
    @details If label input field is empty now ok_btn is hidden, its underline becomes gray,
    the "modified" property is setted to false.\n
    If label input field is filled its underline becomes light green
    and if latitude and longitude fields also filled correctly then ok_btn is showed
    */
    void onLabelChanged(const QString &text);
    /**
    @brief Called when user typed/edited location latitude
    @details If latitude input field is empty now ok_btn is hidden, its underline becomes gray
    and if label input field was automatically filled then it is reseted.\n
    If it is correctly typed then its underline becomes light green,
    if other input fields filled correctly then ok_btn is showed,
    if label input field wasn't automatically filled then it filled with latitude and longitude.\n
    If it isn't correctly typed then its underline becomes red, ok_btn is hidden,
    if label input field was automatically filled then it is reseted.\n
    */
    void onLatitudeChanged();
    /**
    @brief Called when user typed/edited location longitude
    @details If longitude input field is empty now ok_btn is hidden, its underline becomes gray
    and if label input field was automatically filled then it is reseted.\n
    If it is correctly typed then its underline becomes light green,
    if other input fields filled correctly then ok_btn is showed,
    if label input field wasn't automatically filled then it filled with latitude and longitude.\n
    If it isn't correctly typed then its underline becomes red, ok_btn is hidden,
    if label input field was automatically filled then it is reseted.\n
    */
    void onLongitudeChanged();
};

#endif // BASICLOCATIONDIALOG_H
