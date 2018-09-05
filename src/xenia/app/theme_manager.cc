/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2018 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */
#include "theme_manager.h"
#include <QCoreApplication>
#include <QDebug>
#include <QDirIterator>

namespace xe {
namespace app {

ThemeManager::ThemeManager() {}

ThemeManager &ThemeManager::SharedManager() {
  static ThemeManager *manager = nullptr;
  if (!manager) {
    manager = new ThemeManager();
    manager->LoadThemes();
  }
  return *manager;
}

const QString &ThemeManager::base_style() const {
  QFile file(":/res/base.css");
  file.open(QFile::ReadOnly | QFile::Text);

  static QString *style = nullptr;
  if (!style) {
    style = new QString(file.readAll());
    style->remove(QRegExp("[\\n\\t\\r]"));
  }

  return *style;
}

void ThemeManager::LoadThemes() {
  QString theme_dir = QCoreApplication::applicationDirPath() + "/themes";
  QDirIterator iter(theme_dir, QDir::Dirs | QDir::NoDotAndDotDot);

  while (iter.hasNext()) {
    Theme t(iter.next());
    t.LoadTheme();
    themes_.push_back(t);
  }
}

}  // namespace app
}  // namespace xe
