#include <QVBoxLayout>

#include "Grid.h"
#include "MainWindow.h"

MainWindow::MainWindow() {
  createLayout();
}

void MainWindow::createLayout() {
  auto *grid = new Grid(16, 16);

  auto *layout = new QVBoxLayout;
  layout->setContentsMargins(5, 5, 5, 5);
  layout->addWidget(grid);

  auto *w = new QWidget;
  w->setLayout(layout);

  setCentralWidget(w);
}
