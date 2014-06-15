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

private slots:
  void onToolChanged(int index);
  void onColorClicked(const QColor &color);

private:
  void createLayout();

  QComboBox *toolBox;

  ToolKind tool;
  QColor color;
};

#endif // SLD_TOOLBOX_H
