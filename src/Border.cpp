#include <QPainter>

#include "Border.h"

void Border::paint(QPainter &painter) {
  QColor c = color;
  if (previewColor.isValid()) {
    c = previewColor;
    previewColor = QColor();
  }
  painter.fillRect(rect, c);
}

QDataStream &operator<<(QDataStream &stream, const Border &border) {
  stream << border.getRect() << border.getColor() << border.isActive();
  return stream;
}

QDataStream &operator>>(QDataStream &stream, Border &border) {
  QRect rect;
  stream >> rect;
  border.setRect(rect);

  QColor color;
  stream >> color;
  border.setColor(color);

  bool active;
  stream >> active;
  border.setActive(active);
  return stream;
}
