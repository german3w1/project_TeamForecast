#ifndef SCROLLAREAWRAPPER_H
#define SCROLLAREAWRAPPER_H

#include <QScrollArea>
#include <QScrollBar>
#include <QVBoxLayout>

class ScrollAreaWrapper : public QScrollArea
{
    Q_OBJECT
public:
    ScrollAreaWrapper(QWidget *parent);
    QVBoxLayout *scroll_layout;
};

#endif // SCROLLAREAWRAPPER_H
