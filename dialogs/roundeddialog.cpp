#include "dialogs/roundeddialog.h"
#include <QDebug>


QStack<RoundedDialog*> RoundedDialog::opened_dialogs_ = QStack<RoundedDialog*>();

RoundedDialog::RoundedDialog(QWidget *parent, QWidget *dimmable_widget)
: QDialog(parent, Qt::FramelessWindowHint)
{
    if (!opened_dialogs_.isEmpty())
        opened_dialogs_.top()->hide();
    opened_dialogs_.push(this);

    setFocus();
    setAttribute(Qt::WA_TranslucentBackground);
    setStyleSheet(QString("QPushButton { background: %1; color: %2; font: bold 14px; border-radius: 16px; }"
                  "QPushButton::hover { background-color: %3 }"
                  "QLabel {font: bold 12px; color: %2}"
                  "QLabel#title_label {color: %2; font: bold 20px }"
                  "QLineEdit {background : %1; color: %2; border-bottom: 2px solid %3;}")
                  .arg(AppStyle::backgroundColor(ROLE::SECONDARY, STATE::NORMAL).name(),
                  AppStyle::textPrimaryColor().name(),
                  AppStyle::backgroundColor(ROLE::SECONDARY, STATE::HOVERED).name()));

    dimmable_widget_ = dimmable_widget;
    if (auto dw = dimmable_widget_; dw != nullptr) {
        dw->setGraphicsEffect(new DarkOverlayEffect);
        dw->setDisabled(true);
    }

}

RoundedDialog::~RoundedDialog()
{
    opened_dialogs_.pop();
    if (opened_dialogs_.isEmpty()) {
        if (dimmable_widget_!= nullptr) {
            delete dimmable_widget_->graphicsEffect();
            dimmable_widget_->setDisabled(false);
        }
    } else {
        opened_dialogs_.top()->show();
    }
}

void RoundedDialog::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.setBrush(QBrush(AppStyle::backgroundColor(ROLE::SECONDARY, STATE::NORMAL)));
    painter.setPen(Qt::NoPen);

    auto corner_radius = AppStyle::biggestCornerRadius();
    painter.drawRoundedRect(rect(), corner_radius, corner_radius);
}

void RoundedDialog::keyPressEvent(QKeyEvent *event)
{
    if (event->matches(QKeySequence::Cancel))
        deleteLater();
}
