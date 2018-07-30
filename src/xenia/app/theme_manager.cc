#include "theme_manager.h"
#include <QCoreApplication>
#include <QDebug>
#include <QDirIterator>

ThemeManager::ThemeManager() {}

ThemeManager &ThemeManager::SharedManager() {
  static ThemeManager *manager = nullptr;
  if (!manager) {
    manager = new ThemeManager();
    manager->LoadThemes();
  }
  return *manager;
}

void ThemeManager::LoadThemes() {
  QString theme_dir = QCoreApplication::applicationDirPath() + "/themes";
  QDirIterator iter(theme_dir, QDir::Dirs | QDir::NoDotAndDotDot);

  while (iter.hasNext()) {
    qDebug() << iter.next();
  }
}
