#ifndef EXPANDINGWEATHERWIDGET_H
#define EXPANDINGWEATHERWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QStyleOption>
#include <QPainter>
#include <QPropertyAnimation>
#include <QDateTime>
#include <QLabel>

/**
@brief Base widget for Current-, Hourly- and Daily- weather forecast widgets.
@details Provides an opportunity to expand/collapse content
placed in hidden_layout for all inheriting it classes.\n
Also contains some helper functions like getWindDirection(const int &degrees)
and getWeatherIcon(const int &weather_id)
*/

class ExpandingWeatherWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int hidden_height READ getHeight WRITE setHeight) ///< hidden_frame height macro
public:
    /**
    @brief Constructs new ExpandingWeatherWidget
    @param parent Parent for this widget
    */
    ExpandingWeatherWidget(QWidget *parent = nullptr);
    ~ExpandingWeatherWidget();
protected:
    /**
    @brief Helper function
    @param degrees Wind direction in degrees
    @return Wind direction name using parts of the world.\n
    For example: getWindDirection(15) returns "North-East"
    */
    QString getWindDirection(const int &degrees);
    /**
    @brief Helper function
    @param weather_id Weather condition ID. Check out "See also" for more
    @return Icon of weather state placed at pixmap (48x48)
    @see https://openweathermap.org/weather-conditions
    */
    QPixmap getWeatherIcon(const int &weather_id);
    QLabel* generateBoldLabel(const QString &text);
    QLabel* generatePaleLabel();
    /**
    @brief Overrided QWidget::mousePressEvent
    @details This overriding is needed to interact with user pressing the widget.\n
    If hidden_frame is collapsed then it becomes expanded,
    otherwise becomes collapsed
    */
    virtual void mousePressEvent(QMouseEvent *event);
    /**
    @brief Overrided QWidget::paintEvent
    @details This overriding is needed because uses stylesheets mechanizm
    @see https://doc.qt.io/qt-6/stylesheet-reference.html
    */
    virtual void paintEvent(QPaintEvent *event);
    QGridLayout* unhidden_layout;  ///< Layout that contains always visible elements
    QGridLayout* hidden_layout; ///< Layout that contains elements which can be hidden
private:
    QWidget* hidden_frame; ///< Widget containing hidden_layout
    QWidget* unhidden_frame; ///< Widget containing unhidden_layout
    QPropertyAnimation *animation; ///< Expand/collapse hidden_frame animation object
    /**
    @brief setter for Q_PROPERTY hidden_height macro
    @return current hidden_frame height
    */
    int getHeight();
    /**
    @brief setter for Q_PROPERTY hidden_height macro
    @param value New hidden_frame height
    */
    void setHeight(int value);
signals:
    void pressed(ExpandingWeatherWidget *widget);
};

#endif // EXPANDINGWEATHERWIDGET_H
