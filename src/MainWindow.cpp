#include <QFile>
#include <QMenu>
#include <QDebug>
#include <QMenuBar>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QDataStream>

#include "Util.h"
#include "Grid.h"
#include "Toolbox.h"
#include "Version.h"
#include "MainWindow.h"

MainWindow::MainWindow() {
  setWindowTitle(tr("Strategic Layout Designer"));
  createLayout();
  createMenu();
}

void MainWindow::showEvent(QShowEvent *event) {
  Util::centerWidget(this);
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
}

void MainWindow::openProject() {
  QString file =
    QFileDialog::getOpenFileName(this, tr("Open Project"),
                                 QDir::homePath(),
                                 tr("SLD Project (*.sldp)"));
  if (file.isEmpty()) {
    return;
  }

  QFile f(file);
  if (!f.open(QIODevice::ReadOnly)) {
    QMessageBox::warning(this, "sld",
                         tr("Could not open file for reading: %1").arg(file));
    return;
  }

  this->file = file;

  QDataStream stream(&f);
  QString header;
  stream >> header;
  int version;
  stream >> version;
  grid->load(stream, version);
}

void MainWindow::saveProject() {
  save(false);
}

void MainWindow::saveAsProject() {
  save(true);
}

void MainWindow::createLayout() {
  auto *toolbox = new Toolbox;

  grid = new Grid(16, 16, toolbox);

  auto *layout = new QHBoxLayout;
  layout->setContentsMargins(5, 5, 5, 5);
  layout->addWidget(grid);
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
}
