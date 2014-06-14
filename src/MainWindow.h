#ifndef SLD_MAIN_WINDOW_H
#define SLD_MAIN_WINDOW_H

#include <QMainWindow>

class Grid;

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow();

private slots:
  void openProject();
  void saveProject();

private:
  void createLayout();
  void createMenu();

  Grid *grid;
};

#endif // SLD_MAIN_WINDOW_H
