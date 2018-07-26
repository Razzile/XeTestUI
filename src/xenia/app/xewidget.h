#ifndef XEWIDGET_H
#define XEWIDGET_H

#include <QWidget>

/**
 * @brief The XeWidget class
 * Currently unused
 * Will eventually be used as a base widget that
 * all widgets inherit from, giving them built-in
 * theming support
 */
class XeWidget : public QWidget {
  Q_OBJECT
 public:
  explicit XeWidget(QWidget *parent = nullptr);

 signals:

 public slots:
};

#endif  // XEWIDGET_H
