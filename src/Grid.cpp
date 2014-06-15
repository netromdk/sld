#include <QDebug>
#include <QPainter>
#include <QMouseEvent>

#include "Grid.h"
#include "Util.h"
#include "Toolbox.h"

Grid::Grid(int width, int height, Toolbox *toolbox)
  : width(width), height(height), side(30), zoomFactor(1), toolbox(toolbox)
{
  setMouseTracking(true);
  updateSize();
  createGrid();
}

Grid::~Grid() {
  fields.clear();
}

void Grid::clear() {
  zoomFactor = 1;
  fields.clear();
  createGrid();
  update();
}

void Grid::clearBorders() {
  foreach (auto field, fields) {
    field->clearBorders();
  }
  update();
}

void Grid::save(QDataStream &stream) {
  stream << width << height << side << fields.size();
  foreach (const auto field, fields) {
    stream << *field;
  }
}

void Grid::load(QDataStream &stream, int version) {
  stream >> width;
  stream >> height;
  stream >> side;
  updateSize();

  fields.clear();
  int amount;
  stream >> amount;
  for (int i = 0; i < amount; i++) {
    auto *field = new Field;
    stream >> *field;
    fields << FieldPtr(field);
  }

  applyZoom(1);
}

void Grid::applyZoom(float factor) {
  zoomFactor = factor;
  updateSize();

  int i = 0, sside = side * zoomFactor;
  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++, i++) {
      QRect rect(x * sside, y * sside, sside, sside);
      fields[i]->setRect(rect);
    }
  }
  update();
}

void Grid::paintEvent(QPaintEvent *event) {
  QWidget::paintEvent(event);

  QRect prect = event->rect();
  QPainter painter(this);
  foreach (const auto field, fields) {
    const auto &rect = field->getRect();
    if (prect.intersects(rect)) {
      field->paint(painter);
    }
  }
}

void Grid::mouseReleaseEvent(QMouseEvent *event) {
  QWidget::mouseReleaseEvent(event);

  auto field = findField(event->pos());
  if (field) {
    switch (toolbox->getTool()) {
    case ToolKind::Field:
      field->setColor(toolbox->getColor());
      update(field->getRect());
      break;

    case ToolKind::Border:
      int dir =
        field->tryDetectBorder(event->pos(), toolbox->getColor());
      if (dir != -1) {
        CardinalDir ndir = (CardinalDir) dir;
        auto neighbor = findNeighbor(field, ndir);
        if (neighbor) {
          neighbor->setBorder(Util::oppositeDir(ndir), toolbox->getColor());
        }
        update(field->getRect());
      }
      break;
    }
  }
}

void Grid::mouseMoveEvent(QMouseEvent *event) {
  QWidget::mouseMoveEvent(event);

  auto field = findField(event->pos());
  if (field) {
    switch (toolbox->getTool()) {
    case ToolKind::Field:
      field->setPreviewColor(toolbox->getColor());
      update();
      break;

    case ToolKind::Border:
      int dir =
        field->tryDetectBorder(event->pos(), toolbox->getColor(), true);
      if (dir != -1) {
        CardinalDir ndir = (CardinalDir) dir;
        auto neighbor = findNeighbor(field, ndir);
        if (neighbor) {
          neighbor->setBorder(Util::oppositeDir(ndir), toolbox->getColor(),
                              true);
        }
        update();
      }
      break;
    }
  }
}

void Grid::leaveEvent(QEvent *event) {
  QWidget::leaveEvent(event);

  // Re-paint so that previewing fields/borders are cleared.
  update();
}

void Grid::updateSize() {
  // + a little slack.
  QSize size(width * side * zoomFactor + 2, height * side * zoomFactor + 2);
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

FieldPtr Grid::findNeighbor(FieldPtr field, CardinalDir dir) {
  QRect rect = field->getRect();
  switch (dir) {
  case CardinalDir::North:
    rect.translate(0, -1); // Move up a bit
    break;

  case CardinalDir::South:
    rect.translate(0, 1); // Move down a bit
    break;

  case CardinalDir::West:
    rect.translate(-1, 0); // Move west a bit
    break;

  case CardinalDir::East:
    rect.translate(1, 0); // Move east a bit
    break;
  }
  foreach (const auto f, fields) {
    if (f == field) continue;
    if (f->getRect().intersects(rect)) {
      return f;
    }
  }
  return nullptr;
}
