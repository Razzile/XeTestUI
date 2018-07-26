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

  QHBoxLayout* layout = new QHBoxLayout();
  this->centralWidget()->setLayout(layout);

  Sidebar* sidebar = new Sidebar();
  layout->addWidget(sidebar, 0, Qt::AlignLeft);

  QWidget* test_content = new QWidget();
  test_content->setStyleSheet("background: rgb(40,40,40)");
  layout->addWidget(test_content, 1);
}

void MainWidget::paintEvent(QPaintEvent* event) {
  //  QPainter painter(this);
  //  QImage backgroundImage(QStringLiteral(":/res/background.png"));
  //  painter.drawImage(contentsRect(), backgroundImage);
}
