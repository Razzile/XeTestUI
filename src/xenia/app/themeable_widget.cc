/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2018 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */
#include "themeable_widget.h"
#include <QPainter>
#include <QStyleOption>
#include "theme_manager.h"
namespace xe {
namespace app {

ThemeableWidget::ThemeableWidget(const QString &name, QWidget *parent)
    : QWidget(parent) {
  if (name != QString::null) {
    setObjectName(name);
  }

  Theme theme = ThemeManager::SharedManager().current_theme();
  QString style = theme.StylesheetForComponent(objectName());

  if (style != QString::null) {
    setStyleSheet(style);
  }
}

void ThemeableWidget::paintEvent(QPaintEvent *) {
  QStyleOption opt;
  opt.init(this);
  QPainter p(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

}  // namespace app
}  // namespace xe
