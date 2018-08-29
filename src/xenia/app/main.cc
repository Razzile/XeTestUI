#include <QApplication>
#include <QDebug>
#include <QFontDatabase>

#include "main_window.h"
#include "theme_manager.h"

int main(int argc, char *argv[]) {
  QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

  QApplication app(argc, argv);

  auto &manager = xe::app::ThemeManager::SharedManager();

  auto &themes = manager.themes();
  for (auto &theme : themes) {
    qDebug() << theme.directory();

    auto &config = theme.config();

    qDebug() << config.name() << " " << config.description();
  }

  QFontDatabase::addApplicationFont(":/res/ionicons.ttf");

  xe::app::MainWindow w;
  w.setGeometry(100, 100, 640, 360);
  w.show();

  return app.exec();
}
