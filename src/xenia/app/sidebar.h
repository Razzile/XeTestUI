#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QAction>
#include <QToolButton>
#include <QVBoxLayout>
#include <QWidget>

const static int SIDEBAR_DEFAULT_WIDTH = 200;

class Sidebar : public QWidget {
 public:
  Sidebar(int width = SIDEBAR_DEFAULT_WIDTH, QWidget *parent = nullptr);

 private:
  QVBoxLayout *layout_;
  int width_;
};

#endif  // SIDEBAR_H
