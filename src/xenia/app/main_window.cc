/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2018 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */

#include "main_window.h"
#include <QLayout>
#include <QMenuBar>
#include <QToolBar>
#include "main_widget.h"

namespace xe {
namespace app {

MainWindow::MainWindow(QWidget* parent)
    : Themeable<QMainWindow>("MainWindow", parent) {
  QIcon app_icon(":/res/icon.ico");
  setWindowIcon(app_icon);

  QMenuBar* menubar = menuBar();
  QMenu* file_menu = new QMenu("File");
  menubar->addMenu(file_menu);
  QMenu* cpu_menu = new QMenu("CPU");
  menubar->addMenu(cpu_menu);
  QMenu* gpu_menu = new QMenu("GPU");
  menubar->addMenu(gpu_menu);
  QMenu* window_menu = new QMenu("Window");
  menubar->addMenu(window_menu);
  QMenu* help_menu = new QMenu("Help");
  menubar->addMenu(help_menu);
  menubar->setHidden(true);

  file_menu->addAction("Save");
  file_menu->addAction("Exit");

  MainWidget* central_widget = new MainWidget(this);
  this->setCentralWidget(central_widget);
}

}  // namespace app
}  // namespace xe
