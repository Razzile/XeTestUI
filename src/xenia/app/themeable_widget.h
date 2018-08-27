/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2018 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */
#ifndef XEWIDGET_H
#define XEWIDGET_H

#include <QMainWindow>
#include <QPainter>
#include <QStyleOption>
#include <QWidget>
#include "theme_manager.h"

namespace xe {
namespace app {

/**
 * Inherit from this class to automatically theme
 */
template <typename T>
class Themeable : public T {
 public:
  Themeable(QString name = "", QWidget *parent = nullptr) : T(parent) {
    static_assert(std::is_base_of<QObject, T>::value,
                  "T not derived from QObject");
    if (name == QString::null) {
      name = typeid(T).name();
    }
    ApplyTheme(name);
  }
  void ApplyTheme(const QString &name) {
    if (name != QString::null) {
      setObjectName(name);
    }

    Theme theme = ThemeManager::SharedManager().current_theme();
    QString style = theme.StylesheetForComponent(name);

    if (style != QString::null) {
      setStyleSheet(style);
    }
  }

  void paintEvent(QPaintEvent *) override {
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
  }
};

}  // namespace app
}  // namespace xe
#endif  // XEWIDGET_H
