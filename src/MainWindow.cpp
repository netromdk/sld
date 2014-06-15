#include <QFile>
#include <QMenu>
#include <QDebug>
#include <QMenuBar>
#include <QFileInfo>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QDataStream>
#include <QScrollArea>

#include "Util.h"
#include "Grid.h"
#include "Toolbox.h"
#include "Version.h"
#include "MainWindow.h"

MainWindow::MainWindow(const QString &file) : file(file) {
  updateTitle();
  createLayout();
  createMenu();
  resize(700, 530);
}

void MainWindow::showEvent(QShowEvent *event) {
  Util::centerWidget(this);
  if (!file.isEmpty()) {
    load(false);
  }
}

void MainWindow::newProject() {
  QMessageBox::StandardButton res  =
    QMessageBox::question(this, "sld",
                          tr("Are you sure you want to create a new, empty project?"));
  if (res == QMessageBox::No) {
    return;
  }
  file.clear();
  grid->clear();
  toolbox->resetZoom();
  updateTitle();
}

void MainWindow::openProject() {
  load(true);
}

void MainWindow::saveProject() {
  save(false);
}

void MainWindow::saveAsProject() {
  save(true);
}

void MainWindow::clearFields() {
  grid->clear();
}

void MainWindow::clearBorders() {
  grid->clearBorders();
}

void MainWindow::createLayout() {
  toolbox = new Toolbox;

  grid = new Grid(16, 16, toolbox);
  connect(toolbox, &Toolbox::zoomChanged, grid, &Grid::applyZoom);

  auto *scrollArea = new QScrollArea;
  scrollArea->setBackgroundRole(QPalette::Dark);
  scrollArea->setWidget(grid);

  auto *layout = new QHBoxLayout;
  layout->setContentsMargins(5, 5, 5, 5);
  layout->addWidget(scrollArea);
  layout->addWidget(toolbox);

  auto *w = new QWidget;
  w->setLayout(layout);

  setCentralWidget(w);
}

void MainWindow::createMenu() {
  QMenu *fileMenu = menuBar()->addMenu(tr("File"));
  fileMenu->addAction(tr("New project"), this, SLOT(newProject()),
                      QKeySequence::New);
  fileMenu->addAction(tr("Open project"), this, SLOT(openProject()),
                      QKeySequence::Open);
  fileMenu->addAction(tr("Save project"), this, SLOT(saveProject()),
                      QKeySequence::Save);
  fileMenu->addAction(tr("Save as.."), this, SLOT(saveAsProject()),
                      QKeySequence::SaveAs);

  QMenu *editMenu = menuBar()->addMenu(tr("Edit"));
  QMenu *gridEditMenu = editMenu->addMenu(tr("Grid"));
  gridEditMenu->addAction(tr("Clear fields"), this, SLOT(clearFields()));
  gridEditMenu->addAction(tr("Clear borders"), this, SLOT(clearBorders()));
}

void MainWindow::save(bool askFile) {
  QString path;
  if (askFile || this->file.isEmpty()) {
    path =
      QFileDialog::getSaveFileName(this, tr("Save Project"), QString(),
                                   tr("SLD Project (*.sldp)"));
    if (path.isEmpty()) {
      return;
    }
  }
  else {
    path = this->file;
  }

  QFile f(path);
  if (!f.open(QIODevice::WriteOnly)) {
    QMessageBox::warning(this, "sld",
                         tr("Could not open file for writing: %1").arg(path));
    return;
  }

  QDataStream stream(&f);
  stream << QString(PROJECT_HEADER) << (int) PROJECT_VERSION;
  grid->save(stream);

  this->file = path;
  updateTitle();
}

void MainWindow::load(bool askFile) {
  QString path;
  if (askFile || this->file.isEmpty()) {
    path =
      QFileDialog::getOpenFileName(this, tr("Open Project"),
                                   QDir::homePath(),
                                   tr("SLD Project (*.sldp)"));
    if (path.isEmpty()) {
      return;
    }
  }
  else {
    path = this->file;
  }

  QFile f(path);
  if (!f.open(QIODevice::ReadOnly)) {
    QMessageBox::warning(this, "sld",
                         tr("Could not open file for reading: %1").arg(path));
    return;
  }

  toolbox->resetZoom();

  QDataStream stream(&f);
  QString header;
  stream >> header;
  int version;
  stream >> version;
  grid->load(stream, version);

  this->file = path;
  updateTitle();
}

void MainWindow::updateTitle() {
  QString msg;
  if (!file.isEmpty()) {
    msg = " [" + QFileInfo(file).fileName() + "]";
  }
  setWindowTitle(tr("Strategic Layout Designer%1").arg(msg));
}
