#include <QDebug>
#include <QLabel>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "Toolbox.h"
#include "ColorWidget.h"

Toolbox::Toolbox() : tool(ToolKind::Field), color(Qt::white) {
  setFixedWidth(150);
  createLayout();
}

void Toolbox::createLayout() {
  toolBox = new QComboBox;
  toolBox->addItem(tr("Field"), (int) ToolKind::Field);
  toolBox->addItem(tr("Border"), (int) ToolKind::Border);
  connect(toolBox, SIGNAL(currentIndexChanged(int)),
          this, SLOT(onToolChanged(int)));

  auto *toolLayout = new QHBoxLayout;
  toolLayout->setContentsMargins(0, 0, 0, 0);
  toolLayout->addWidget(new QLabel(tr("Tool")));
  toolLayout->addWidget(toolBox);
  toolLayout->addStretch();

  auto *colorWidget = new ColorWidget;
  connect(colorWidget, &ColorWidget::colorClicked,
          this, &Toolbox::onColorClicked);
  colorWidget->setCurrentIndex(0);

  zoomBox = new QComboBox;
  for (int i = 25; i <= 800; i += 25) {
    zoomBox->addItem(tr("%1%").arg(i), i);
  }
  zoomBox->setCurrentIndex(zoomBox->findData(100));
  connect(zoomBox, SIGNAL(currentIndexChanged(int)),
          this, SLOT(onZoomChanged(int)));

  auto *zoomLayout = new QHBoxLayout;
  zoomLayout->setContentsMargins(0, 0, 0, 0);
  zoomLayout->addWidget(new QLabel(tr("Zoom")));
  zoomLayout->addWidget(zoomBox);

  auto *layout = new QVBoxLayout;
  layout->setContentsMargins(0, 0, 0, 0);
  layout->addLayout(toolLayout);
  layout->addWidget(new QLabel(tr("Color")));
  layout->addWidget(colorWidget);
  layout->addLayout(zoomLayout);
  layout->addStretch();
  
  setLayout(layout);
}

void Toolbox::resetZoom() {
  zoomBox->setCurrentIndex(zoomBox->findData(100));
}

void Toolbox::onToolChanged(int index) {
  tool = (ToolKind) toolBox->itemData(index).toInt();
}

void Toolbox::onColorClicked(const QColor &color) {
  this->color = color;
}

void Toolbox::onZoomChanged(int index) {
  emit zoomChanged(zoomBox->itemData(index).toFloat() / 100.0);
}
