#include "appstyle.h"

AppStyle::AppStyle()
{

}

void AppStyle::setTheme(QString theme)
{
    current_theme_ = theme;
}

QColor AppStyle::backgroundColor(ROLE role, STATE state)
{
    return background_colors[current_theme_][role][state];
}

QString AppStyle::current_theme_ = "default_day";
double AppStyle::biggest_corner_radius_  = 20;
double AppStyle::medium_corner_radius_   = 16;
double AppStyle::smallest_corner_radius_ = 10;


QHash<QString, QHash<ROLE, QHash<STATE, QColor>>> AppStyle::background_colors = {
    { "default_day",   {
          {ROLE::PRIMARY, {
                   {STATE::NORMAL,  QColor(255, 171, 64)},
                   {STATE::HOVERED, QColor(255, 152, 0)},
                   {STATE::PRESSED, QColor(255, 152, 0)}
          }
      },
          {ROLE::SECONDARY, {
                   {STATE::NORMAL,  QColor(255, 255, 255)},
                   {STATE::HOVERED, QColor(224, 224, 224)},
                   {STATE::PRESSED, QColor(224, 224, 224)}
          }
      }
    }
    },
    { "default_night",   {
          {ROLE::PRIMARY, {
                   {STATE::NORMAL,  QColor(1, 87, 155)},
                   {STATE::HOVERED, QColor(1, 75, 133)},
                   {STATE::PRESSED, QColor(1, 75, 133)}
          }
      },
          {ROLE::SECONDARY, {
                   {STATE::NORMAL,  QColor(55, 71, 79)},
                   {STATE::HOVERED, QColor(45, 57, 64)},
                   {STATE::PRESSED, QColor(45, 57, 64)}
          }
      }
    }
    },
};


const QHash<QString, QColor> AppStyle::text_primary_colors_ = {
    { "default_day", QColor(0,0,0) },
    { "default_night", QColor(255,255,255) }
};
