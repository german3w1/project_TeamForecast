#ifndef SCROLLAREAWRAPPER_H
#define SCROLLAREAWRAPPER_H

#include <QScrollArea>
#include <QScrollBar>
#include <QVBoxLayout>

/**
@brief Small wrapper over QScrollArea
@details Here nothing to say. I added it to make
the logic of the code more transparent
*/

class ScrollAreaWrapper : public QScrollArea
{
    Q_OBJECT
    QFrame* scroll_frame;
public:
    ScrollAreaWrapper(QWidget *parent = nullptr);
    QVBoxLayout *scroll_layout;
    void clear();
};

#endif // SCROLLAREAWRAPPER_H