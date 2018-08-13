#ifndef THEME_H
#define THEME_H

#include <QString>
#include <QVector>
#include "theme_configuration.h"

enum ThemeRes { THEME_LOAD_OK = 0, THEME_NOT_FOUND, THEME_MISCONFIGURED };

class Theme {
 public:
  Theme() = default;
  Theme(const QString &directory) : directory_(directory) {}
  Theme(const ThemeConfiguration &config) : config_(config) {}

  ThemeRes LoadTheme();

  const QString &directory() const { return directory_; }
  const ThemeConfiguration &config() const { return config_; }

 private:
  QString directory_;
  ThemeConfiguration config_;
};
#endif  // THEME_H
