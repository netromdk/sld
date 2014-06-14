#include <QDebug>
#include <QLabel>
#include <QVBoxLayout>

#include "Toolbox.h"
#include "ColorWidget.h"

Toolbox::Toolbox() {
  setFixedWidth(200);
  createLayout();
}

void Toolbox::createLayout() {
  auto *colorWidget = new ColorWidget;
  connect(colorWidget, &ColorWidget::colorClicked,
          this, &Toolbox::onColorClicked);
  colorWidget->setCurrentIndex(0);
  
  auto *layout = new QVBoxLayout;
  layout->setContentsMargins(0, 0, 0, 0);
  layout->addWidget(new QLabel(tr("Color")));
  layout->addWidget(colorWidget);
  layout->addStretch();
  
  setLayout(layout);
}

void Toolbox::onColorClicked(const QColor &color) {
  this->color = color;
}
