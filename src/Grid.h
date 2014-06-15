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

  void clear();
  void clearBorders();

  void save(QDataStream &stream);
  void load(QDataStream &stream, int version);

public slots:
  void applyZoom(float factor);

protected:
  void paintEvent(QPaintEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);
  void leaveEvent(QEvent *event);

private:
  void updateSize();
  void createGrid();
  FieldPtr findField(const QPoint &pos);
  FieldPtr findNeighbor(FieldPtr field, CardinalDir dir);
  
  int width, height, side;
  float zoomFactor;
  Toolbox *toolbox;
  QList<FieldPtr> fields;
};

#endif // SLD_GRID_H
