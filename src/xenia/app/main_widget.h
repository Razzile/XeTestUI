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

#include <QKeyEvent>
#include <QMainWindow>
#include <QPainter>
#include <QPushButton>
#include <QToolBar>
#include "themeable_widget.h"

namespace xe {
namespace app {

class MainWindow;

class MainWidget : public Themeable<QWidget> {
  Q_OBJECT
 public:
  explicit MainWidget(QWidget *parent = nullptr);

 protected:
  void keyPressEvent(QKeyEvent *e) override;
  void keyReleaseEvent(QKeyEvent *e) override;

 private:
  MainWindow *window_;

 signals:

 public slots:
};

}  // namespace app
}  // namespace xe

#endif  // WIDGET_H
