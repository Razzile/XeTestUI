#include <QApplication>
#include <QFontDatabase>

#include "theme_manager.h"

#ifdef _WIN32
#include "win/native_widget_win.h"
#else
#include "main_widget.h"
#endif

int main(int argc, char *argv[]) {
  QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

  QApplication app(argc, argv);

  ThemeManager manager = ThemeManager::SharedManager();

  QFontDatabase::addApplicationFont(":/res/ionicons.ttf");

  // A common feature is to save your app's geometry on close such that you can
  // draw in the same place on relaunch Thus this project supports specifying
  // the X/Y/Width/Height in a cross-platform manner
  int windowXPos, windowYPos, windowWidth, windowHeight;
  windowXPos = 100;
  windowYPos = 100;
  windowWidth = 1280;
  windowHeight = 720;

  MainWidget w;

  w.setGeometry(windowXPos, windowYPos, windowWidth, windowHeight);
  w.show();

  return app.exec();
}
