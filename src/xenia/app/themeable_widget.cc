/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2018 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */
#include "themeable_widget.h"

namespace xe {
namespace app {

// template <>
// void Themeable<QWidget>::ApplyTheme(const QString &name) {
//  if (name != QString::null) {
//    setObjectName(name);
//  }

//  Theme theme = ThemeManager::SharedManager().current_theme();
//  QString style = theme.StylesheetForComponent(name);

//  if (style != QString::null) {
//    setStyleSheet(style);
//  }
//}

// template <>
// Themeable<QWidget>::Themeable(const QString &name, QWidget *parent)
//    : QWidget(parent) {
//  ApplyTheme(name);
//}

// template <>
// void Themeable<QWidget>::paintEvent(QPaintEvent *) {
//  QStyleOption opt;
//  opt.init(this);
//  QPainter p(this);
//  style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
//}

// template <>
// Themeable<QMainWindow>::Themeable(const QString &name, QWidget *parent)
//    : QMainWindow(parent) {
//  reinterpret_cast<Themeable<QWidget> *>(this)->ApplyTheme(name);
//}

// template <>
// void Themeable<QMainWindow>::paintEvent(QPaintEvent *) {
//  QStyleOption opt;
//  opt.init(this);
//  QPainter p(this);
//  style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
//}

}  // namespace app
}  // namespace xe
