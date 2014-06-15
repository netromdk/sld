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

int Field::tryDetectBorder(const QPoint &pos, const QColor &color,
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

        // Return the direction the border was found.
        return (int) key;
      }

      // Stop here because no other field will contain the point.
      break;
    }
  }

  return -1;
}

void Field::setBorder(CardinalDir dir, const QColor &color, bool preview) {
  auto &border = borders[dir];
  border.active = true;
  if (preview) {
    border.previewColor = color;
  }
  else {
    border.color = color;
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
  float slack = 0.16;
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
  const auto &borders = field.getBorders();
  stream << borders.size();
  foreach (auto key, borders.keys()) {
    stream << (int) key << borders[key];
  }
  return stream;
}

QDataStream &operator>>(QDataStream &stream, Field &field) {
  QRect rect;
  stream >> rect;
  field.setRect(rect);

  QColor color;
  stream >> color;
  field.setColor(color);

  int borderLen;
  stream >> borderLen;
  QMap<CardinalDir, Border> borders;
  for (int i = 0; i < borderLen; i++) {
    int type;
    stream >> type;
    Border border;
    stream >> border;
    borders[(CardinalDir) type] = border;
  }
  field.setBorders(borders);
  return stream;
}

QDataStream &operator<<(QDataStream &stream, const Border &border) {
  stream << border.rect << border.color << border.active;
  return stream;
}

QDataStream &operator>>(QDataStream &stream, Border &border) {
  stream >> border.rect;
  stream >> border.color;
  stream >> border.active;
  return stream;
}
