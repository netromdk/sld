#include "Field.h"

Field::Field() { }

Field::Field(const QRect &rect, const QColor &color)
  : rect(rect), color(color)
{ }

bool Field::containsPoint(const QPoint &pos) const {
  return rect.contains(pos);
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
