#ifndef SCROLLAREAWRAPPER_H
#define SCROLLAREAWRAPPER_H

#include <QScrollArea>
#include <QScrollBar>
#include <QVBoxLayout>

class ScrollAreaWrapper : public QScrollArea
{
public:
    ScrollAreaWrapper(QWidget *parent);
    QVBoxLayout *scroll_layout;
    void addWidget(QWidget *widget);
private:

};

#endif // SCROLLAREAWRAPPER_H
