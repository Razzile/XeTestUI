#ifndef THEMEMANAGER_H
#define THEMEMANAGER_H

#include <QColor>
#include <QString>
#include <QVector>
#include "theme.h"
class ThemeManager {
 public:
  static ThemeManager& SharedManager();

  const QVector<Theme>& themes() const { return themes_; }

 private:
  void LoadThemes();
  Theme LoadTheme(const QString& name);
  ThemeManager();

  QVector<Theme> themes_;
};

#endif  // THEMEMANAGER_H
