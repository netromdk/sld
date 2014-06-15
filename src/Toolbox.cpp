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

  auto *layout = new QVBoxLayout;
  layout->setContentsMargins(0, 0, 0, 0);
  layout->addLayout(toolLayout);
  layout->addWidget(new QLabel(tr("Color")));
  layout->addWidget(colorWidget);
  layout->addStretch();
  
  setLayout(layout);
}

void Toolbox::onToolChanged(int index) {
  tool = (ToolKind) toolBox->itemData(index).toInt();
}

void Toolbox::onColorClicked(const QColor &color) {
  this->color = color;
}
