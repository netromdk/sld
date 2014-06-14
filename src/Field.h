#ifndef SLD_FIELD_H
#define SLD_FIELD_H

#include <QRect>
#include <QColor>

#include <memory>

class Field;
typedef std::shared_ptr<Field> FieldPtr;

class Field {
public:
  Field(const QRect &rect, const QColor &color);

  const QRect &getRect() const { return rect; }
  bool containsPoint(const QPoint &pos) const;

  const QColor &getColor() const  { return color; }
  void setColor(const QColor &color) { this->color = color; }

private:
  QRect rect;
  QColor color;
};

#endif // SLD_FIELD_H
