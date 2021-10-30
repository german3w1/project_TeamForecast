#include "roundedmenu.h"
#include <QDebug>
#include <QFrame>
RoundedMenu::RoundedMenu(LocationModel* model, LocationsManager* manager, QPoint pos, QWidget* parent)
    : QWidget(parent)
{
    model_ = model;
    manager_ = manager;
    move(pos);
    setWindowFlags(Qt::FramelessWindowHint
        | Qt::WindowStaysOnTopHint | Qt::Popup | Qt::NoDropShadowWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_DeleteOnClose);
    auto menu_layout = new QVBoxLayout();
    menu_layout->setSpacing(0);
    menu_layout->setContentsMargins(0, 6, 0, 6);
    setLayout(menu_layout);

    edit_btn = new AnimatedButton("Изменить", ROLE::SECONDARY, 0);
    edit_btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    edit_btn->connect(edit_btn, &AnimatedButton::clicked, this, &RoundedMenu::onEditBtnClicked);
    menu_layout->addWidget(edit_btn);

    delete_btn = new AnimatedButton("Удалить", ROLE::SECONDARY, 0);
    delete_btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    delete_btn->connect(delete_btn, &AnimatedButton::clicked, this, &RoundedMenu::onDeleteBtnClicked);
    menu_layout->addWidget(delete_btn);

    copy_btn = new AnimatedButton("Копировать", ROLE::PRIMARY, 0);
    copy_btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    edit_btn->connect(copy_btn, &AnimatedButton::clicked, this, &RoundedMenu::onCopyBtnClicked);
    menu_layout->addWidget(copy_btn);

    update_btn = new AnimatedButton("Обновить", ROLE::SECONDARY, 0);
    update_btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    update_btn->connect(update_btn, &AnimatedButton::clicked, this, &RoundedMenu::onUpdateBtnClicked);
    menu_layout->addWidget(update_btn);

    setMinimumHeight(sizeHint().height() * 1.6);
    setMaximumWidth(sizeHint().width() * 1.6);
}

void RoundedMenu::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); // Включаем сглаживание

    painter.setBrush(QBrush(AppStyle::backgroundColor(ROLE::PRIMARY, STATE::NORMAL)));
    painter.setPen(Qt::NoPen); // Край уведомления не будет выделен

    painter.drawRoundedRect(rect(), 6, 6);
}

void RoundedMenu::focusOutEvent(QFocusEvent* event)
{
    Q_UNUSED(event);
}

void RoundedMenu::onCopyBtnClicked()
{
    auto name = model_->label();
    auto latitude = QString("Широта: %1").arg(model_->latitude());
    auto longitude = QString("Долгота: %1").arg(model_->longitude());
    QApplication::clipboard()->setText(name + "\n" + latitude + "\n" + longitude);
    deleteLater();
}

void RoundedMenu::onDeleteBtnClicked()
{
    manager_->deleteModel(model_);
}

void RoundedMenu::onEditBtnClicked()
{
    auto dialog = new EditLocationDialog(parentWidget()->parentWidget()->parentWidget()->parentWidget()->parentWidget()->parentWidget(), *model_);
    dialog->show();
}
