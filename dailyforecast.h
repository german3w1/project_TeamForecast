#ifndef DAILYFORECAST_H
#define DAILYFORECAST_H

#include <QFrame>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QList>
#include <QVariantMap>
#include <dailywidget.h>

class DailyForecast : public QFrame
{
public:
    DailyForecast(QWidget *parent);
    ~DailyForecast();
    void update_weather_info(const QList<QVariant> &new_daily_dataset, const int &offset);
private:
    QVBoxLayout *m_main_layout;
    QFrame *m_scroll_frame;
    QVBoxLayout *m_scroll_frame_layout;
    QScrollArea *m_scroll_area;
    DailyWidget *m_daily_widgets[8];
private slots:
    void onWidgetPressed(DailyWidget *widget);
};

#endif // DAILYFORECAST_H
