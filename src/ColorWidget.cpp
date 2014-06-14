#include <QGridLayout>

#include "ColorWidget.h"
#include "ColorButton.h"

ColorWidget::ColorWidget() {
  createLayout();
  setup();
}

void ColorWidget::createLayout() {
  layout = new QGridLayout;
  layout->setContentsMargins(0, 0, 0, 0);
  setLayout(layout);
}

void ColorWidget::setup() {
  static QList<QColor> colors;
  if (colors.isEmpty()) {
    colors << Qt::red << Qt::green << Qt::blue << Qt::cyan << Qt::yellow
           << Qt::gray << Qt::magenta << Qt::black << Qt::white;
  }
  for (int i = 0, row = 0, col = 0; i < colors.size(); i++, col++) {
    if (col >= 4) {
      col = 0;
      row++;
    }
    addButton(colors[i], row, col);
  }
}

void ColorWidget::addButton(const QColor &color, int row, int column) {
  auto *btn = new ColorButton(color);
  connect(btn, SIGNAL(colorClicked(const QColor&)),
          SIGNAL(colorClicked(const QColor&)));
  layout->addWidget(btn, row, column);
}
