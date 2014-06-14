#include <QDebug>
#include <QPainter>
#include <QMouseEvent>

#include "Grid.h"

Grid::Grid(int width, int height)
  : width(width), height(height), side(30)
{
  QSize size(width * side, height * side);
  setMinimumSize(size);
  createGrid();
}

Grid::~Grid() {
  fields.clear();
}

void Grid::paintEvent(QPaintEvent *event) {
  QWidget::paintEvent(event);

  QRect prect = event->rect();

  QPainter painter(this);
  foreach (const auto field, fields) {
    const auto &rect = field->getRect();
    if (!prect.contains(rect)) {
      continue;
    }

    const auto &clr = field->getColor();
    painter.fillRect(rect, clr);
    painter.setPen(Qt::black);
    painter.drawRect(rect);
  }
}

void Grid::mouseReleaseEvent(QMouseEvent *event) {
  QWidget::mouseReleaseEvent(event);

  auto field = findField(event->pos());
  if (field) {
    field->setColor(Qt::green);
    update(field->getRect());
  }
}

void Grid::createGrid() {
  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      QRect rect(x * side, y * side, side, side);
      fields << FieldPtr(new Field(rect, Qt::white));
    }
  }
}

FieldPtr Grid::findField(const QPoint &pos) {
  foreach (const auto field, fields) {
    if (field->containsPoint(pos)) {
      return field;
    }
  }
  return nullptr;
}
