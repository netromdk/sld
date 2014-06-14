#include <QPixmap>

#include "ColorButton.h"

ColorButton::ColorButton(const QColor &color) : color(color) {
  QPixmap pix(16, 16);
  pix.fill(color);
  setIcon(QIcon(pix));
}

void ColorButton::mouseReleaseEvent(QMouseEvent *event) {
  QToolButton::mouseReleaseEvent(event);
  setDown(true);
  emit colorClicked(color);
}
