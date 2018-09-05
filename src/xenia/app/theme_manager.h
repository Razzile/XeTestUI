/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2018 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */
#ifndef THEMEMANAGER_H
#define THEMEMANAGER_H

#include <QColor>
#include <QString>
#include <QVector>
#include "theme.h"

namespace xe {
namespace app {

class ThemeManager {
 public:
  static ThemeManager& SharedManager();
  const Theme& current_theme() const { return themes_.front(); }
  const QVector<Theme>& themes() const { return themes_; }
  const QString& base_style() const;

 private:
  void LoadThemes();
  Theme LoadTheme(const QString& name);
  ThemeManager();

  QVector<Theme> themes_;
};

}  // namespace app
}  // namespace xe
#endif  // THEMEMANAGER_H
