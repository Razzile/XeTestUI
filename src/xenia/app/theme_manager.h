#ifndef THEMEMANAGER_H
#define THEMEMANAGER_H

#include <QColor>
#include <QString>
#include <vector>

class Theme {
  using ThemeColor = std::pair<QString, QColor>;

 public:
  QColor operator[](const QString& str) const;
  QColor& operator[](const QString& str);

 private:
  std::vector<ThemeColor> colors_;
};
class ThemeManager {
 public:
  static ThemeManager& SharedManager();

  Theme theme() const;

 private:
  ThemeManager();

  Theme theme_;
};

#endif  // THEMEMANAGER_H
