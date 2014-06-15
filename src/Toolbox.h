#ifndef SLD_TOOLBOX_H
#define SLD_TOOLBOX_H

#include <QWidget>

class QComboBox;

enum class ToolKind : int {
  Field,
  Border
};

class Toolbox : public QWidget {
  Q_OBJECT

public:
  Toolbox();

  ToolKind getTool() const { return tool; }
  const QColor& getColor() const { return color; }

  void resetZoom();

signals:
  void zoomChanged(float factor);

private slots:
  void onToolChanged(int index);
  void onColorClicked(const QColor &color);
  void onZoomChanged(int index);

private:
  void createLayout();

  QComboBox *toolBox, *zoomBox;

  ToolKind tool;
  QColor color;
};

#endif // SLD_TOOLBOX_H
