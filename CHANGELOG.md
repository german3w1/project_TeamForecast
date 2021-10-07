# Changelog
### v2.0.3
- Build system was changed from `QMake` to `CMake`, so _TeamForecast&#46;pro_ was replaced with _CMakeLists&#46;text_.

### v2.0.2
- `LocationModel` automatically updates after it created with `LocationManager`.
- `LocationsManagerView` became a singleton to prevent multiple creation on click of a button
- `LocationsManager` became a singleton to simplify access to it from settings dialog.
- Added _update_timer_ and _setUpdateInterval(int msec)_ to `LocationsManager` (I'll test auto-updating models).
- Fixed bug: you could mark location as favorite and then changed location, but it was still considered marked as favorite.

### v2.0.1
- Introduced Model-View pattern: base [`AbstractWeatherModel`](https://github.com/german3w1/project_TeamForecast/blob/master/models/abstractweathermodel.h) inherited by [`CurrentModel`](https://github.com/german3w1/project_TeamForecast/blob/master/models/currentmodel.h), [`HourlyModel`](https://github.com/german3w1/project_TeamForecast/blob/master/models/hourlymodel.h) and [`DailyModel`](https://github.com/german3w1/project_TeamForecast/blob/master/models/dailymodel.h). Most of functions moved to them. The functions of converting the values of temperature, distance, wind speed and pressure into non-standard units of measure have been implemented (so far, you cannot switch them from the application)
- Redesigned navigation between added locations: instead of creating every time new `LocationForecast` widget and storing it in `QTabWidget` I made [`LocationsManager`](https://github.com/german3w1/project_TeamForecast/blob/master/models/locationsmanager.h)(which contains all added locations models and provide some functionality to manage them) , [`LocationsManagerView`](https://github.com/german3w1/project_TeamForecast/blob/master/dialogs/locationsmanagerview.h)(dialog-widget with search line, which is view for `LocationsManager` and [`LocationMiniView`](https://github.com/german3w1/project_TeamForecast/blob/master/views/locationminiview.h), which shows some info about each [`LocationModel`](https://github.com/german3w1/project_TeamForecast/blob/master/models/locationmodel.h)(click left mouse button to switch current shown location, right to call context `RoundedMenu`, which allows: edit location, copy, delete or update). Now exists only one instance of `LocationForecast` which has an opportunity to display selected by user `LocationModel` or nothing in case user selected nothing.
- Average RAM usage for each location with new architecture decreased from _15-20mb_ to _0.3-1.0mb_.
- Most of sources were grouped into folders.
- All dialogs now inherit [`RoundedDialog`](https://github.com/german3w1/project_TeamForecast/blob/master/dialogs/roundeddialog.h)(dialog with round corners). 
- Created [`AppStyle`](https://github.com/german3w1/project_TeamForecast/blob/master/base/appstyle.h) class(Provides **current theme**, element's **roles** enum and element's **states** enum).
- Created base class for animated widgets - [`AnimatedWidget`](https://github.com/german3w1/project_TeamForecast/blob/master/base/animatedwidget.h). In it I implemented animation in the style of material design.
- Created [`AnimatedButton`](https://github.com/german3w1/project_TeamForecast/blob/master/base/animatedbutton.h) inherits `AnimatedWidget`.
- Created [`TextWidget`](https://github.com/german3w1/project_TeamForecast/blob/master/base/textwidget.h) as a replace for `QLabel` text.
- Added `clear()` function to `ScrollAreaWrapper`.
- Opacity value in `DarkOverlayEffect` constructor.
- Some slots replaced with lambdas.
- `updateWidgetInfo(...)` functions in `CurrentWidget`, `HourlyWidget` and `DailyWidget` were simplified using models.
- `ExpandingWeatherWidget`: now inherits `AnimatedWidget`. Temporary disabled expanding animation.
- and many other minor changes.