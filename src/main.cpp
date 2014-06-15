#include <QTimer>
#include <QApplication>

#include "Version.h"
#include "MainWindow.h"

int main(int argc, char **argv) {
  QApplication app(argc, argv);
  QCoreApplication::setApplicationName("sld");
  QCoreApplication::setApplicationVersion(versionString());

  QString file;
  if (argc > 1) {
    file = QString::fromUtf8(argv[1]);
  }

  // Start in event loop.
  MainWindow main(file);
  QTimer::singleShot(0, &main, SLOT(show()));

  return app.exec();
}
