#ifndef SLD_FIELD_H
#define SLD_FIELD_H

#include <QRect>

class Field {
public:
  Field(const QRect &rect);

  const QRect &getRect() const { return rect; }

private:
  QRect rect;
};

#endif // SLD_FIELD_H
