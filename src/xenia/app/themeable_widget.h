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

// TODO: this class may not be needed as
// QApplication::setStylesheet() can set global styles
class ThemeableWidget : public QWidget {
  Q_OBJECT
 public:
  explicit ThemeableWidget(const QString &widget_name = "",
                           QWidget *parent = nullptr);
  void paintEvent(QPaintEvent *) override;
 signals:

 public slots:
};

}  // namespace app
}  // namespace xe
#endif  // XEWIDGET_H
