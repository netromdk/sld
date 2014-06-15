#include <QDebug>
#include <QPainter>

#include "Field.h"

Field::Field() { }

Field::Field(const QRect &rect, const QColor &color)
  : rect(rect), color(color), previewColor(QColor())
{
  updateBorders();
}

void Field::setRect(const QRect &rect) {
  this->rect = rect;
  updateBorders();
}

bool Field::containsPoint(const QPoint &pos) const {
  return rect.contains(pos);
}

void Field::tryDetectBorder(const QPoint &pos, const QColor &color,
                            bool preview) {
  foreach (auto key, borders.keys()) {
    Border &border = borders[key];
    auto &rect = border.rect;
    if (rect.contains(pos)) {
      bool ok = true;
      float slack = 0.2;

      // Ignore if at the corners.
      switch (key) {
      case CardinalDir::North:
      case CardinalDir::South:
        ok = (pos.x() >= rect.x() + rect.width() * slack &&
              pos.x() <= rect.x() + rect.width() * (1 - slack));
        break;

      case CardinalDir::West:
      case CardinalDir::East:
        ok = (pos.y() >= rect.y() + rect.height() * slack &&
              pos.y() <= rect.y() + rect.height() * (1 - slack));
        break;
      }

      if (ok) {
        border.active = true;
        if (preview) {
          border.previewColor = color;
        }
        else {
          border.color = color;
        }
      }
    }
  }
}

void Field::paint(QPainter &painter) {
  QColor c = color;
  if (previewColor.isValid()) {
    c = previewColor;
    previewColor = QColor();
  }
  painter.fillRect(rect, c);

  painter.setPen(QColor("#99D8F9"));
  painter.drawRect(rect);

  foreach (auto key, borders.keys()) {
    auto &border = borders[key];
    if (border.active) {
      QColor c = border.color;
      if (border.previewColor.isValid()) {
        c = border.previewColor;
        border.previewColor = QColor();
      }
      painter.fillRect(border.rect, c);
    }
  }
}

void Field::updateBorders() {
  float slack = 0.25;
  int w = rect.width() * slack;
  borders.clear();

  Border border;
  border.rect = QRect(rect.topLeft(), QSize(rect.width(), w));
  borders[CardinalDir::North] = border;

  QRect r(rect.topLeft(), QSize(rect.width(), w));
  r.translate(0, rect.height() - w);
  border = Border();
  border.rect = r;
  borders[CardinalDir::South] = border;

  border = Border();
  border.rect = QRect(rect.topLeft(), QSize(w, rect.height()));
  borders[CardinalDir::West] = border;

  r = QRect(rect.topLeft(), QSize(w, rect.height()));
  r.translate(rect.height() - w, 0);
  border = Border();
  border.rect = r;
  borders[CardinalDir::East] = border;
}

QDataStream &operator<<(QDataStream &stream, const Field &field) {
  stream << field.getRect() << field.getColor();
  return stream;
}

QDataStream &operator>>(QDataStream &stream, Field &field) {
  QRect rect;
  stream >> rect;
  field.setRect(rect);

  QColor color;
  stream >> color;
  field.setColor(color);
  return stream;
}
