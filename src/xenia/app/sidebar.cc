#include "sidebar.h"
#include <IconsIonicons.h>
#include <QFont>
#include <QHBoxLayout>
#include <QLabel>

Sidebar::Sidebar(int width, QWidget *parent) : QWidget(parent), width_(width) {
  layout_ = new QVBoxLayout();
  layout_->setSpacing(0);
  layout_->setMargin(0);
  setLayout(layout_);

  // setStyleSheet("background-color: black");

  setMinimumWidth(width_);
  setMaximumWidth(width_);

  QFont icon_font("Ionicons", 32);

  QToolButton *home_button = new QToolButton();
  home_button->setText(ICON_II_IOS_HOME_OUTLINE);
  home_button->setAutoRaise(true);
  home_button->setFont(icon_font);
  home_button->setStyleSheet("color: white");
  layout_->addWidget(home_button, 0, Qt::AlignCenter);

  QToolButton *library_button = new QToolButton();
  library_button->setText(ICON_II_IOS_GAME_CONTROLLER_B_OUTLINE);
  library_button->setAutoRaise(true);
  library_button->setFont(icon_font);
  library_button->setStyleSheet("color: white");
  layout_->addWidget(library_button, 0, Qt::AlignCenter);

  QToolButton *settings_button = new QToolButton();
  settings_button->setText(ICON_II_IOS_SETTINGS);
  settings_button->setAutoRaise(true);
  settings_button->setFont(icon_font);
  settings_button->setStyleSheet("color: white");
  layout_->addWidget(settings_button, 0, Qt::AlignCenter);

  QToolButton *help_button = new QToolButton();
  help_button->setText(ICON_II_IOS_HELP_OUTLINE);
  help_button->setAutoRaise(true);
  help_button->setFont(icon_font);
  help_button->setStyleSheet("color: white");
  layout_->addWidget(help_button, 0, Qt::AlignCenter);
}
