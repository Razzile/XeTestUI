/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2018 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */
#ifndef WIDGET_H
#define WIDGET_H

#include <QMainWindow>
#include <QPainter>
#include <QPushButton>
#include <QToolBar>
#include "themeable_widget.h"

namespace xe {
namespace app {

class MainWidget : public Themeable<QWidget> {
  Q_OBJECT
 public:
  explicit MainWidget(QWidget* parent = 0);

 signals:

 public slots:
};

}  // namespace app
}  // namespace xe

#endif  // WIDGET_H
