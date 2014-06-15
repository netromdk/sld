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
