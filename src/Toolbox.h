#ifndef SLD_TOOLBOX_H
#define SLD_TOOLBOX_H

#include <QWidget>

class Toolbox : public QWidget {
public:
  Toolbox();

  const QColor& getColor() const { return color; }

private slots:
  void onColorClicked(const QColor &color);

private:
  void createLayout();

  QColor color;
};

#endif // SLD_TOOLBOX_H
