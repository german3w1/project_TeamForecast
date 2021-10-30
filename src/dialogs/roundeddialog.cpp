#include "dialogs/roundeddialog.h"
#include <QDebug>

QStack<RoundedDialog*> RoundedDialog::opened_dialogs_ = QStack<RoundedDialog*>();
bool RoundedDialog::need_animate_overlay_ = true;

RoundedDialog::RoundedDialog(QWidget* parent, QWidget* dimmable_widget)
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

    title_ = new TextWidget("", 16, true, ROLE::SECONDARY);
    title_->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
}

RoundedDialog::~RoundedDialog()
{
}

void RoundedDialog::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.setBrush(QBrush(AppStyle::backgroundColor(ROLE::SECONDARY, STATE::NORMAL)));
    painter.setPen(Qt::NoPen);

    auto corner_radius = AppStyle::biggestCornerRadius();
    painter.drawRoundedRect(rect(), corner_radius, corner_radius);
}

void RoundedDialog::keyPressEvent(QKeyEvent* event)
{
    if (event->matches(QKeySequence::Cancel))
        closeDialog();
}

void RoundedDialog::closeDialog()
{
    opened_dialogs_.pop();
    if (opened_dialogs_.isEmpty()) {
        if (dimmable_widget_) {
            auto effect = qobject_cast<DarkOverlayEffect*>(dimmable_widget_->graphicsEffect());
            auto anim = new QPropertyAnimation(effect, "opacity_");
            anim->setEasingCurve(QEasingCurve::Linear);
            anim->setStartValue(effect->opacity());
            anim->setEndValue(1);
            anim->setDuration(100);
            anim->start(QAbstractAnimation::DeleteWhenStopped);
            connect(
                anim, &QPropertyAnimation::finished,
                [this]() {
                    dimmable_widget_->graphicsEffect()->deleteLater();
                    dimmable_widget_->setDisabled(false);
                    need_animate_overlay_ = true;
                });
        }
    } else {
        opened_dialogs_.top()->show();
    }
    auto anim = new QPropertyAnimation(this, "windowOpacity");
    connect(
        anim, &QPropertyAnimation::finished,
        this, &QWidget::deleteLater);
    anim->setEasingCurve(QEasingCurve::Linear);
    anim->setStartValue(1.0);
    anim->setEndValue(0);
    anim->setDuration(200);
    anim->start(QAbstractAnimation::DeleteWhenStopped);
}

void RoundedDialog::showEvent(QShowEvent* event)
{
    QDialog::showEvent(event);
    animateAppearence();
}

void RoundedDialog::hideEvent(QHideEvent* event)
{
    auto anim = new QPropertyAnimation(this, "windowOpacity");
    anim->setEasingCurve(QEasingCurve::Linear);
    anim->setStartValue(1.0);
    anim->setEndValue(0);
    anim->setDuration(200);
    anim->start(QAbstractAnimation::DeleteWhenStopped);
    QDialog::hideEvent(event);
}

void RoundedDialog::open()
{
    QDialog::open();
    animateAppearence();
}

void RoundedDialog::animateAppearence()
{
    auto anim1 = new QPropertyAnimation(this, "windowOpacity");
    anim1->setEasingCurve(QEasingCurve::Linear);
    anim1->setStartValue(0);
    anim1->setEndValue(1.0);
    anim1->setDuration(200);
    anim1->start(QAbstractAnimation::DeleteWhenStopped); /**/

    if (need_animate_overlay_ && dimmable_widget_) {
        auto effect = qobject_cast<DarkOverlayEffect*>(dimmable_widget_->graphicsEffect());
        auto anim = new QPropertyAnimation(effect, "opacity_");
        anim->setEasingCurve(QEasingCurve::Linear);
        anim->setStartValue(1);
        anim->setEndValue(0.3);
        anim->setDuration(100);
        anim->start(QAbstractAnimation::DeleteWhenStopped);
        need_animate_overlay_ = false;
    }
}
