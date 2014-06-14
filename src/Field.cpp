#include <QPainter>

#include "Field.h"

Field::Field() { }

Field::Field(const QRect &rect, const QColor &color)
  : rect(rect), color(color), previewColor(QColor())
{ }

bool Field::containsPoint(const QPoint &pos) const {
  return rect.contains(pos);
}

void Field::paint(QPainter &painter) {
  QColor c = color;
  if (previewColor.isValid()) {
    c = previewColor;
    previewColor = QColor();
  }
  painter.fillRect(rect, c);
  painter.setPen(QColor("#000F55")); // pen blue
  painter.drawRect(rect);
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
