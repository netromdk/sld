#ifndef SLD_COLOR_BUTTON_H
#define SLD_COLOR_BUTTON_H

#include <QToolButton>

class ColorButton : public QToolButton {
  Q_OBJECT

public:
  ColorButton(const QColor &color);

signals:
  void colorClicked(const QColor &color);

protected:
  void mouseReleaseEvent(QMouseEvent *event);
  
private:
  QColor color;
};

#endif // SLD_COLOR_BUTTON_H
