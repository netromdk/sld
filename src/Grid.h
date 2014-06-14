#ifndef SLD_GRID_H
#define SLD_GRID_H

#include <QList>
#include <QWidget>

#include "Field.h"

class Grid : public QWidget {
public:
  Grid(int width, int height);
  ~Grid();

protected:
  void paintEvent(QPaintEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);

private:
  void createGrid();
  FieldPtr findField(const QPoint &pos);
  
  int width, height, side;
  QList<FieldPtr> fields;
};

#endif // SLD_GRID_H
