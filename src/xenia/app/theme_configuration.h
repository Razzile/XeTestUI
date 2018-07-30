#ifndef THEME_CONFIGURATION_H
#define THEME_CONFIGURATION_H

#include <QString>
#include <memory>

class ThemeConfiguration {
 public:
  ThemeConfiguration(const QString &config_file);

  static std::unique_ptr<ThemeConfiguration> FromFile(const QString &file);

 private:
  QString name_;
  QString description_:
};

#endif  // THEME_CONFIGURATION_H
