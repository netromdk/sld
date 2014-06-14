#include <QDebug>
#include <QPainter>
#include <QMouseEvent>

#include "Grid.h"
#include "Toolbox.h"

Grid::Grid(int width, int height, Toolbox *toolbox)
  : width(width), height(height), side(30), toolbox(toolbox)
{
  updateSize();
  createGrid();
}

Grid::~Grid() {
  fields.clear();
}

void Grid::save(QDataStream &stream) {
  stream << width << height;
  stream << fields.size();
  foreach (const auto field, fields) {
    stream << *field;
  }
}

void Grid::load(QDataStream &stream, int version) {
  stream >> width;
  stream >> height;
  updateSize();

  fields.clear();
  int amount;
  stream >> amount;
  for (int i = 0; i < amount; i++) {
    auto *field = new Field;
    stream >> *field;
    fields << FieldPtr(field);
  }
  update();
}

void Grid::paintEvent(QPaintEvent *event) {
  QWidget::paintEvent(event);

  QRect prect = event->rect();
  QPainter painter(this);
  foreach (const auto field, fields) {
    const auto &rect = field->getRect();
    if (!prect.intersects(rect)) {
      continue;
    }

    const auto &clr = field->getColor();
    painter.fillRect(rect, clr);
    painter.setPen(QColor("#000F55")); // pen blue
    painter.drawRect(rect);
  }
}

void Grid::mouseReleaseEvent(QMouseEvent *event) {
  QWidget::mouseReleaseEvent(event);

  auto field = findField(event->pos());
  if (field) {
    field->setColor(toolbox->getColor());
    update(field->getRect());
  }
}

void Grid::updateSize() {
  QSize size(width * side, height * side);
  setMinimumSize(size);
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
