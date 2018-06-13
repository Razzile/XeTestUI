#include "theme_manager.h"

QColor Theme::operator[](const QString &str) const {
  auto it =
      std::find_if(colors_.begin(), colors_.end(),
                   [&](const ThemeColor &pair) { return pair.first == str; });
  if (it == colors_.end()) {
    return QColor(0, 0, 0, 0);
  }
  return it->second;
}

QColor &Theme::operator[](const QString &str) {
  auto it =
      std::find_if(colors_.begin(), colors_.end(),
                   [&](const ThemeColor &pair) { return pair.first == str; });
  if (it == colors_.end()) {
    colors_.push_back({str, QColor(0, 0, 0, 0)});
    return colors_.back().second;
  }
  return it->second;
}

ThemeManager::ThemeManager() {
  theme_["background"] = QColor(30, 30, 30);
  theme_["background-light"] = QColor(45, 45, 45);
  theme_["text"] = Qt::white;

  //  theme_["background"] = Qt::white;
  //  theme_["background-light"] = Qt::white;
  //  theme_["text"] = QColor(10, 10, 10);

  //  theme_["background"] = QColor(180, 30, 120);
  //  theme_["background-light"] = QColor(45, 45, 45);
  //  theme_["text"] = Qt::white;
}

Theme ThemeManager::theme() const { return theme_; }

ThemeManager &ThemeManager::SharedManager() {
  static ThemeManager *manager = nullptr;
  if (!manager) {
    manager = new ThemeManager();
  }
  return *manager;
}
