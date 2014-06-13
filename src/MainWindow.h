#ifndef SLD_MAIN_WINDOW_H
#define SLD_MAIN_WINDOW_H

#include <QMainWindow>

class MainWindow : public QMainWindow {
public:
  MainWindow();

private:
  void createLayout();
};

#endif // SLD_MAIN_WINDOW_H
