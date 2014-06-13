#include <QDebug>
#include <QPainter>

#include "Grid.h"

Grid::Grid(int width, int height)
  : width(width), height(height), side(30)
{
  QSize size(width * side, height * side);
  setMinimumSize(size);
  createGrid();
}

void Grid::paintEvent(QPaintEvent *event) {
  QWidget::paintEvent(event);

  QPainter painter(this);
  foreach (const auto &field, fields) {
    const auto &rect = field.getRect();
    const auto &clr = field.getColor();
    painter.fillRect(rect, clr);
    painter.setPen(Qt::black);
    painter.drawRect(rect);
  }
}

void Grid::createGrid() {
  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      QRect rect(x * side, y * side, side, side);
      fields << Field(rect, Qt::white);
    }
  }
}
