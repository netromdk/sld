#ifndef SLD_GRID_H
#define SLD_GRID_H

#include <QList>
#include <QWidget>

#include "Field.h"

class Toolbox;
class QDataStream;

class Grid : public QWidget {
public:
  Grid(int width, int height, Toolbox *toolbox);
  ~Grid();

  void save(QDataStream &stream);
  void load(QDataStream &stream, int version);

protected:
  void paintEvent(QPaintEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);

private:
  void updateSize();
  void createGrid();
  FieldPtr findField(const QPoint &pos);
  
  int width, height, side;
  Toolbox *toolbox;
  QList<FieldPtr> fields;
};

#endif // SLD_GRID_H
