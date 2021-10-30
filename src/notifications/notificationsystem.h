#ifndef NOTIFICATIONSYSTEM_H
#define NOTIFICATIONSYSTEM_H

#include <QObject>

class NotificationSystem : public QObject
{
    Q_OBJECT
public:
    explicit NotificationSystem(QObject *parent = nullptr);

signals:

};

#endif // NOTIFICATIONSYSTEM_H
