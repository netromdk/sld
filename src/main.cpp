#include <QTimer>
#include <QApplication>

#include "Version.h"
#include "MainWindow.h"

int main(int argc, char **argv) {
  QApplication app(argc, argv);
  QCoreApplication::setApplicationName("sld");
  QCoreApplication::setApplicationVersion(versionString());

  // Start in event loop.
  MainWindow main;
  QTimer::singleShot(0, &main, SLOT(show()));

  return app.exec();
}
