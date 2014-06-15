#ifndef SLD_MAIN_WINDOW_H
#define SLD_MAIN_WINDOW_H

#include <QMainWindow>

class Grid;

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow();

protected:
  void showEvent(QShowEvent *event);

private slots:
  void newProject();
  void openProject();
  void saveProject();

private:
  void createLayout();
  void createMenu();

  Grid *grid;
  QString file;
};

#endif // SLD_MAIN_WINDOW_H
