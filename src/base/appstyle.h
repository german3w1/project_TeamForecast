#ifndef APPSTYLE_H
#define APPSTYLE_H
#include <QColor>
#include <QHash>
#include <QString>

enum STATE : char {
    NORMAL,
    HOVERED,
    PRESSED,
    SELECTED
};

enum ROLE : char {
    PRIMARY,
    SECONDARY,
    MENU
};

class AppStyle {
public:
    AppStyle();
    static void setTheme(QString theme);
    static double biggestCornerRadius() { return biggest_corner_radius_; }
    static double mediumCornerRadius() { return medium_corner_radius_; }
    static double smallestCornerRadius() { return smallest_corner_radius_; }
    static QColor backgroundColor(ROLE role, STATE state);
    static QColor textPrimaryColor()
    {
        return text_primary_colors_[current_theme_];
    }

private:
    static QString current_theme_;
    static double biggest_corner_radius_;
    static double medium_corner_radius_;
    static double smallest_corner_radius_;
    static QHash<QString, QHash<ROLE, QHash<STATE, QColor>>> background_colors;
    static const QHash<QString, QColor> text_primary_colors_;
};

#endif // APPSTYLE_H
