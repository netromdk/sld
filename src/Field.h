#ifndef SLD_FIELD_H
#define SLD_FIELD_H

#include <QRect>
#include <QColor>

class Field {
public:
  Field(const QRect &rect, const QColor &color);

  const QRect &getRect() const { return rect; }
  const QColor &getColor() const  { return color; }

private:
  QRect rect;
  QColor color;
};

#endif // SLD_FIELD_H
