/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2018 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */
#include <QApplication>
#include <QLabel>
#include <QLayout>
#include <QMenuBar>
#include <QStyle>
#include <QUrl>

#include "main_widget.h"
#include "sidebar.h"
#include "theme_manager.h"

namespace xe {
namespace app {

MainWidget::MainWidget(QWidget* parent)
    : Themeable<QWidget>("MainWidget", parent) {
  QHBoxLayout* layout = new QHBoxLayout();
  layout->setContentsMargins(0, 0, 0, 0);
  setLayout(layout);

  Sidebar* sidebar = new Sidebar();
  layout->addWidget(sidebar, 0, Qt::AlignLeft);

  QWidget* test_content = new QWidget();
  test_content->setObjectName("test");
  test_content->setStyleSheet("background: rgb(40,40,40)");
  layout->addWidget(test_content, 1);
}

}  // namespace app
}  // namespace xe
