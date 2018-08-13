#include "theme_configuration.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

bool ThemeConfiguration::LoadFromFile() { return LoadFromFile(file_); }

bool ThemeConfiguration::LoadFromFile(const QString &filename) {
  if (filename.isNull() || filename.isEmpty()) {
    return false;
  }

  QFile file;
  file.setFileName(filename);

  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    return false;
  }

  auto text = file.readAll();

  QJsonDocument json_doc = QJsonDocument::fromJson(text);
  QJsonObject json_obj = json_doc.object();

  QJsonValue name_obj = json_obj["name"];
  QJsonValue desc_obj = json_obj["description"];

  if (name_obj.isString() && desc_obj.isString()) {
    name_ = name_obj.toString();
    description_ = desc_obj.toString();

    return true;
  } else {
    return false;
  }
}

bool ThemeConfiguration::SaveToFile() { return SaveToFile(file_); }

bool ThemeConfiguration::SaveToFile(const QString &filename) {
  if (filename.isNull() || filename.isEmpty()) {
    return false;
  }

  QJsonObject root;
  root["name"] = name_;
  root["description"] = description_;

  QJsonDocument document(root);

  QFile file;
  file.setFileName(filename);

  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    return false;
  }

  if (file.write(document.toJson()) < 0) {
    return false;
  }

  file.flush();
  file.close();

  return true;
}

const std::unique_ptr<ThemeColor> ThemeConfiguration::ColorForKey(
    const QString &key) {
  for (const auto &color : colors_) {
    if (color.first == key) {
      return std::unique_ptr<ThemeColor>(new ThemeColor(color));
    }
  }
  return nullptr;
}

void ThemeConfiguration::add_color(const QString &name, const QColor &color) {
  colors_.emplace_back(name, color);
}

void ThemeConfiguration::add_color(const QString &name, const QString &hex) {
  return add_color(name, QColor(hex));
}

void ThemeConfiguration::add_color(const QString &name, int r, int g, int b) {
  return add_color(name, QColor(r, g, b));
}

void ThemeConfiguration::add_color(const QString &name, int r, int g, int b,
                                   int a) {
  return add_color(name, QColor(r, g, b, a));
}
