#ifndef ROUNDEDDIALOG_H
#define ROUNDEDDIALOG_H
#include <QDialog>
#include <QGraphicsColorizeEffect>
#include <QPainter>
#include <QStack>
#include <src/base/animatedbutton.h>
#include <src/base/appstyle.h>
#include <src/base/textwidget.h>
#include <src/darkoverlayeffect.h>

class RoundedDialog : public QDialog {
    Q_OBJECT
public:
    static QStack<RoundedDialog*> opened_dialogs_;
    static bool need_animate_overlay_;
    RoundedDialog(QWidget* parent, QWidget* dimmable_widget = nullptr);
    virtual ~RoundedDialog();
    virtual void open() override;

protected:
    TextWidget* title_;
    virtual void paintEvent(QPaintEvent* event) override;
    virtual void keyPressEvent(QKeyEvent* event) override;
    virtual void closeDialog();
    virtual void showEvent(QShowEvent* event) override;
    virtual void hideEvent(QHideEvent* event) override;

private:
    QWidget* dimmable_widget_;
    void animateAppearence();
};

#endif // ROUNDEDDIALOG_H
