/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2018 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "themeable_widget.h"

namespace xe {
namespace app {

class MainWindow : public Themeable<QMainWindow> {
  Q_OBJECT
 public:
  explicit MainWindow(QWidget* parent = nullptr);

  QString window_title() const { return window_title_; }

 private:
  QString window_title_;

 signals:

 public slots:
};

}  // namespace app
}  // namespace xe

#endif  // MAIN_WINDOW_H
