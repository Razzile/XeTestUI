#ifndef THEME_H
#define THEME_H

#include <QString>
#include <QVector>

enum ThemeRes { THEME_LOAD_OK = 0, THEME_NOT_FOUND, THEME_MISCONFIGURED };

class Theme {
  using ThemeColor = std::pair<QString, QColor>;

 public:
  Theme(const QString &directory);

  ThemeRes LoadTheme();

  const QVector<ThemeColor> colors() const { return colors_; }
  QColor *ColorForKey(const QString &key);

 private:
  QString directory_;
  QVector<ThemeColor> colors_;
};
#endif  // THEME_H
