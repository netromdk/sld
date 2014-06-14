#ifndef SLD_COLOR_WIDGET_H
#define SLD_COLOR_WIDGET_H

#include <QWidget>

class QGridLayout;

class ColorWidget : public QWidget {
  Q_OBJECT
  
public:
  ColorWidget();

signals:
  void colorClicked(const QColor &color);

private:
  void createLayout();
  void setup();
  void addButton(const QColor &color, int row, int column);

  QGridLayout *layout;
};

#endif // SLD_COLOR_WIDGET_H
