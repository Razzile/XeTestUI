#ifndef THEME_CONFIGURATION_H
#define THEME_CONFIGURATION_H

#include <QString>
#include <memory>

class ThemeConfiguration {
 public:
  static std::unique_ptr<ThemeConfiguration> FromFile(const QString &file);

 private:
  ThemeConfiguration();
  ThemeConfiguration(QString name, QString desc);

  void set_name(const QString &name);
  void set_description(const QString &desc);

  QString name_;
  QString description_:
};

#endif  // THEME_CONFIGURATION_H
