#ifndef ROUNDEDDIALOG_H
#define ROUNDEDDIALOG_H
#include <QStack>
#include <QDialog>
#include <base/appstyle.h>
#include <QPainter>
#include <darkoverlayeffect.h>
#include <base/animatedbutton.h>
#include <base/textwidget.h>

class RoundedDialog : public QDialog
{
    Q_OBJECT
public:
    static QStack<RoundedDialog*> opened_dialogs_;
    RoundedDialog(QWidget *parent, QWidget *dimmable_widget = nullptr);
    virtual ~RoundedDialog();
protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);
private:
    QWidget *dimmable_widget_;
};

#endif // ROUNDEDDIALOG_H
