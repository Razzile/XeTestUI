#include "main_widget.h"

#include <QApplication>
#include <QLabel>
#include <QLayout>
#include <QMenuBar>
#include <QStyle>
#include <QUrl>

#include "sidebar.h"
#include "theme_manager.h"

MainWidget::MainWidget(QWidget* parent) : QMainWindow(parent) {
  window_title_ = "Xenia";  // move to qwinwidget maybe?

  QIcon app_icon(":/res/icon.ico");
  setWindowIcon(app_icon);

  Theme theme = ThemeManager::SharedManager().theme();

  QPalette Pal(palette());
  Pal.setColor(QPalette::Background, theme["background"]);
  setAutoFillBackground(true);
  setPalette(Pal);

  // Windows example of adding a toolbar + min/max/close buttons
#ifdef _WIN32

  // Add the toolbar
  window_toolbar_ = new QToolBar(this);
  window_toolbar_->setMovable(false);
  window_toolbar_->setFloatable(false);
  window_toolbar_->setStyleSheet("background-color: none; border: none;");
  addToolBar(window_toolbar_);

  // Create a transparent-to-mouse-events widget that pads right for a fixed
  // width equivalent to min/max/close buttons
  QWidget* btn_spacer = new QWidget(window_toolbar_);
  btn_spacer->setAttribute(Qt::WA_TransparentForMouseEvents);
  btn_spacer->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
  btn_spacer->setStyleSheet("background-color: none; border: none;");
  btn_spacer->setFixedWidth(135 /* rough width of close/min/max buttons */);
  // toolBar->addWidget(btnSpacer);

  // Create a title label just because
  QLabel* title_label = new QLabel(window_title_);
  title_label->setFixedWidth(160);
  title_label->setStyleSheet(QString("color:%1;").arg(theme["text"].name()));
  // titleLabel->setAlignment(Qt::AlignHCenter);
  // Set it transparent to mouse events such that you can click and drag when
  // moused over the label
  title_label->setAttribute(Qt::WA_TransparentForMouseEvents);

  // Create spacer widgets to keep the title centered
  QWidget* left_spacer = new QWidget(window_toolbar_);
  QWidget* right_spacer = new QWidget(window_toolbar_);

  // Set them transparent to mouse events + auto-expanding in size
  left_spacer->setAttribute(Qt::WA_TransparentForMouseEvents);
  left_spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  left_spacer->setStyleSheet("background-color: none; border: none;");
  right_spacer->setAttribute(Qt::WA_TransparentForMouseEvents);
  right_spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  right_spacer->setStyleSheet("background-color: none; border: none;");

  QLabel* app_icon_label = new QLabel();
  app_icon_label->setPixmap(app_icon.pixmap(QSize(18, 18)));
  app_icon_label->setMargin(0);
  app_icon_label->setContentsMargins(4, 2, 4, 2);

  window_toolbar_->addWidget(app_icon_label);
  window_toolbar_->addWidget(title_label);
  window_toolbar_->addWidget(right_spacer);

  QIcon close_icon = QIcon(QStringLiteral(":/res/close.svg"));
  QIcon max_icon = QIcon(QStringLiteral(":/res/maximize.svg"));
  QIcon min_icon = QIcon(QStringLiteral(":/res/minimize.svg"));
  // Create the min/max/close buttons
  min_button_ = new QPushButton();
  max_button_ = new QPushButton();
  close_button_ = new QPushButton();

  min_button_->setIcon(min_icon);
  max_button_->setIcon(max_icon);
  close_button_->setIcon(close_icon);
  min_button_->setIconSize(QSize(12, 12));
  max_button_->setIconSize(QSize(12, 12));
  close_button_->setIconSize(QSize(12, 12));

  min_button_->setStyleSheet(
      "QPushButton{background: transparent; border-radius:0;}");
  max_button_->setStyleSheet(
      "QPushButton{background: transparent; border-radius:0;}");
  close_button_->setStyleSheet(
      "QPushButton{background: transparent; border-radius:0;}");

  max_button_->setCheckable(true);

  min_button_->setMinimumSize(45, 22);
  max_button_->setMinimumSize(45, 22);
  close_button_->setMinimumSize(45, 22);

  window_toolbar_->addWidget(min_button_);
  window_toolbar_->addWidget(max_button_);
  window_toolbar_->addWidget(close_button_);
  window_toolbar_->layout()->setAlignment(min_button_, Qt::AlignTop);
  window_toolbar_->layout()->setAlignment(max_button_, Qt::AlignTop);
  window_toolbar_->layout()->setAlignment(close_button_, Qt::AlignTop);

  // toolBar->layout()->setMenuBar(menuBar);

  addToolBarBreak();

  // An actual app should use icons for the buttons instead of text
  // and style the different button states / widget margins in css

#endif

  QToolBar* menu_toolbar = new QToolBar();
  menu_toolbar->setMovable(false);
  menu_toolbar->setFloatable(false);
  menu_toolbar->setStyleSheet("background-color: none; border: none;");

  QMenuBar* menubar = new QMenuBar();
  menubar->setStyleSheet(QString("color:%1;").arg(theme["text"].name()));
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

  file_menu->addAction("Save");
  file_menu->addAction("Exit");

  menu_toolbar->layout()->setMenuBar(menubar);
  addToolBar(menu_toolbar);

  QWidget* central_widget = new QWidget();
  this->setCentralWidget(central_widget);

  QVBoxLayout* layout = new QVBoxLayout();
  this->centralWidget()->setLayout(layout);

  Sidebar* sidebar = new Sidebar();
  layout->addWidget(sidebar);
}

void MainWidget::paintEvent(QPaintEvent* event) {
  //  QPainter painter(this);
  //  QImage backgroundImage(QStringLiteral(":/res/background.png"));
  //  painter.drawImage(contentsRect(), backgroundImage);
}
