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

#include <QWidget>

namespace xe {
namespace app {

class ThemeableWidget : public QWidget {
  Q_OBJECT
 public:
  explicit ThemeableWidget(QWidget *parent = nullptr);

 signals:

 public slots:
};

}  // namespace app
}  // namespace xe
#endif  // XEWIDGET_H
