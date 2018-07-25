#include "sidebar.h"
#include <IconsIonicons.h>
#include <QFont>
#include <QHBoxLayout>
#include <QLabel>

Sidebar::Sidebar(int width, QWidget *parent) : QWidget(parent), width_(width) {
  layout_ = new QVBoxLayout();
  setLayout(layout_);

  // setStyleSheet("background-color: black");

  setMinimumWidth(width_);
  setMaximumWidth(width_);

  QFont font("Ionicons", 32);

  QWidget *sidebar_title = new QWidget();
  sidebar_title->setMaximumHeight(100);

  QHBoxLayout *sidebar_header_layout = new QHBoxLayout();
  sidebar_header_layout->setSpacing(0);

  sidebar_title->setLayout(sidebar_header_layout);

  QPixmap xenia_pixmap(":/res/icon.ico");
  xenia_pixmap = xenia_pixmap.scaled(32, 32, Qt::KeepAspectRatio,
                                     Qt::SmoothTransformation);

  QLabel *xenia_logo = new QLabel();
  xenia_logo->setPixmap(xenia_pixmap);
  sidebar_header_layout->addWidget(xenia_logo);

  QVBoxLayout *sidebar_title_layout = new QVBoxLayout();
  sidebar_title_layout->setSpacing(0);
  sidebar_header_layout->addLayout(sidebar_title_layout);

  QFont header_font("Segoe UI", 18, QFont::Bold);

  QLabel *xenia_header = new QLabel("Xenia");
  xenia_header->setFont(header_font);
  xenia_header->setStyleSheet("color: white");
  sidebar_title_layout->addWidget(xenia_header, 0, Qt::AlignTop);

  QLabel *xenia_footer = new QLabel("build: 724086d");
  xenia_footer->setStyleSheet("color: grey");
  sidebar_title_layout->addWidget(xenia_footer, 0, Qt::AlignTop);

  layout_->addWidget(sidebar_title, 0, Qt::AlignTop);

  QToolButton *home_button = new QToolButton();
  home_button->setText(ICON_II_IOS_HOME_OUTLINE);
  home_button->setAutoRaise(true);
  home_button->setFont(font);
  home_button->setStyleSheet("color: white");
  layout_->addWidget(home_button);

  QToolButton *library_button = new QToolButton();
  library_button->setText(ICON_II_IOS_GAME_CONTROLLER_B_OUTLINE);
  library_button->setAutoRaise(true);
  library_button->setFont(font);
  library_button->setStyleSheet("color: white");
  layout_->addWidget(library_button);

  QToolButton *settings_button = new QToolButton();
  settings_button->setText(ICON_II_IOS_SETTINGS);
  settings_button->setAutoRaise(true);
  settings_button->setFont(font);
  settings_button->setStyleSheet("color: white");
  layout_->addWidget(settings_button);

  QToolButton *help_button = new QToolButton();
  help_button->setText(ICON_II_IOS_HELP_OUTLINE);
  help_button->setAutoRaise(true);
  help_button->setFont(font);
  help_button->setStyleSheet("color: white");
  layout_->addWidget(help_button);
}
