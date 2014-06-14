#include <QHBoxLayout>

#include "Grid.h"
#include "Toolbox.h"
#include "MainWindow.h"

MainWindow::MainWindow() {
  createLayout();
}

void MainWindow::createLayout() {
  auto *toolbox = new Toolbox;

  auto *grid = new Grid(16, 16, toolbox);

  auto *layout = new QHBoxLayout;
  layout->setContentsMargins(5, 5, 5, 5);
  layout->addWidget(grid);
  layout->addWidget(toolbox);

  auto *w = new QWidget;
  w->setLayout(layout);

  setCentralWidget(w);
}
