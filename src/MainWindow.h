#ifndef SLD_MAIN_WINDOW_H
#define SLD_MAIN_WINDOW_H

#include <QMainWindow>

class Grid;
class Toolbox;

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(const QString &file = QString());

protected:
  void showEvent(QShowEvent *event);

private slots:
  void newProject();
  void openProject();
  void saveProject();
  void saveAsProject();
  void clearFields();
  void clearBorders();

private:
  void createLayout();
  void createMenu();
  void save(bool askFile = true);
  void load(bool askFile = true);
  void updateTitle();

  Toolbox *toolbox;
  Grid *grid;
  QString file;
};

#endif // SLD_MAIN_WINDOW_H
