/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2018 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */
#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QAction>
#include <QToolButton>
#include <QVBoxLayout>
#include <QWidget>
#include "themeable_widget.h"

namespace xe {
namespace app {

class Sidebar : public Themeable<QWidget> {
 public:
  Sidebar(QWidget *parent = nullptr);

 private:
  QVBoxLayout *layout_;
};

}  // namespace app
}  // namespace xe

#endif  // SIDEBAR_H
