#include <QGridLayout>

#include "ColorWidget.h"
#include "ColorButton.h"

ColorWidget::ColorWidget() {
  createLayout();
  setup();
}

void ColorWidget::setCurrentIndex(int idx) {
  if (idx < 0 || idx > buttons.size() - 1) {
    return;
  }
  auto *btn = buttons[idx];
  btn->click();
  btn->setDown(true);
}

void ColorWidget::onColorClicked(const QColor &color) {
  auto *btn = qobject_cast<ColorButton*>(sender());
  if (!btn) return;
  foreach (auto *b, buttons) {
    if (b != btn) {
      b->setDown(false);
    }
  }
  emit colorClicked(color);
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
  connect(btn, &ColorButton::colorClicked, this, &ColorWidget::onColorClicked);
  layout->addWidget(btn, row, column);
  buttons << btn;
}
