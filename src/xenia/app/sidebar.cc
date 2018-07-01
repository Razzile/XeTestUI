#include "sidebar.h"
#include <QFont>

Sidebar::Sidebar(int width, QWidget *parent) : QWidget(parent), width_(width) {
  layout_ = new QVBoxLayout();
  setLayout(layout_);

  setStyleSheet("background-color: black");

  setMaximumWidth(width_);

  for (int i = 0; i < 5; i++) {
    QToolButton *test = new QToolButton();
    test->setText("S");
    test->setAutoRaise(true);

    QFont font("Arial", 60);
    test->setFont(font);
    test->setStyleSheet("color: white");

    layout()->addWidget(test);
  }
}
