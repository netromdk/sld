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
  void saveAsProject();

private:
  void createLayout();
  void createMenu();
  void save(bool askFile = true);

  Grid *grid;
  QString file;
};

#endif // SLD_MAIN_WINDOW_H
