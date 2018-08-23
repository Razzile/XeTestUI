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

namespace xe {
namespace app {

class MainWidget : public QMainWindow {
  Q_OBJECT
 public:
  explicit MainWidget(QWidget* parent = 0);

  QString window_title() const { return window_title_; }

  QToolBar* window_toolbar() const { return window_toolbar_; }

  QPushButton* max_button() const { return max_button_; }
  QPushButton* min_button() const { return min_button_; }
  QPushButton* close_button() const { return close_button_; }

 protected:
  void paintEvent(QPaintEvent* event);

 private:
  QString window_title_;
  // If you want to have Max/Min/Close buttons, look at how QWinWidget uses
  // these
  // TODO: move these to a win/button_toolbar class
  QPushButton* max_button_ = nullptr;
  QPushButton* min_button_ = nullptr;
  QPushButton* close_button_ = nullptr;
  // If you want to enable dragging the window when the mouse is over top of,
  // say, a QToolBar, then look at how QWinWidget uses this
  QToolBar* window_toolbar_ = nullptr;

 signals:

 public slots:
};

}  // namespace app
}  // namespace xe

#endif  // WIDGET_H
