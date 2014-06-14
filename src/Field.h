#ifndef SLD_FIELD_H
#define SLD_FIELD_H

#include <QRect>
#include <QColor>
#include <QDataStream>

#include <memory>

class QPainter;

class Field;
typedef std::shared_ptr<Field> FieldPtr;

class Field {
public:
  Field();
  Field(const QRect &rect, const QColor &color);

  const QRect &getRect() const { return rect; }
  void setRect(const QRect &rect) { this->rect = rect; }
  bool containsPoint(const QPoint &pos) const;

  const QColor &getColor() const  { return color; }
  void setColor(const QColor &color) { this->color = color; }
  void setPreviewColor(const QColor &color) { previewColor = color; }

  void paint(QPainter &painter);

private:
  QRect rect;
  QColor color, previewColor;
};

QDataStream &operator<<(QDataStream &stream, const Field &field);
QDataStream &operator>>(QDataStream &stream, Field &field);

#endif // SLD_FIELD_H
