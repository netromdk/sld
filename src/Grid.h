#ifndef SLD_GRID_H
#define SLD_GRID_H

#include <QList>
#include <QWidget>

#include "Field.h"

class Grid : public QWidget {
public:
  Grid(int width, int height);

protected:
  void paintEvent(QPaintEvent *event);

private:
  void createGrid();
  
  int width, height, side;
  QList<Field> fields;
};

#endif // SLD_GRID_H
