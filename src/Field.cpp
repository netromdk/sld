#include "Field.h"

Field::Field(const QRect &rect, const QColor &color)
  : rect(rect), color(color)
{ }

bool Field::containsPoint(const QPoint &pos) const {
  return rect.contains(pos);
}
