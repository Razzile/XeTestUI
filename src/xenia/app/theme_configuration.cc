#include "theme_configuration.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

ThemeConfiguration::ThemeConfiguration() {}

std::unique_ptr<ThemeConfiguration> ThemeConfiguration::FromFile(
    const QString &file) {
  QFile file;
  file.setFileName(file);

  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    return nullptr;
  }

  auto text = file.readAll();

  QJsonDocument json_doc = QJsonDocument::fromJson(text);
  QJsonObject json_obj = json_doc.object();

  QJsonValue name_obj = json_obj["name"];
  QJsonValue desc_obj = json_obj["description"];

  if (name_obj.isString() && desc_obj.isString()) {
    ThemeConfiguration *config =
        new ThemeConfiguration(name_obj.toString(), desc_obj.toString());
    return std::make_unique<ThemeConfiguration>(config);
  } else {
    return nullptr;
  }
}
