#ifndef SLD_FIELD_H
#define SLD_FIELD_H

#include <QMap>
#include <QRect>
#include <QColor>
#include <QDataStream>

#include <memory>

#include "Border.h"
#include "CardinalDir.h"

class QPainter;

class Field;
typedef std::shared_ptr<Field> FieldPtr;

class Field {
public:
  Field();
  Field(const QRect &rect, const QColor &color);

  const QRect &getRect() const { return rect; }
  void setRect(const QRect &rect);
  bool containsPoint(const QPoint &pos) const;

  const QColor &getColor() const  { return color; }
  void setColor(const QColor &color) { this->color = color; }
  void setPreviewColor(const QColor &color) { previewColor = color; }
  int tryDetectBorder(const QPoint &pos, const QColor &color,
                      bool preview = false);

  const QMap<CardinalDir, BorderPtr> &getBorders() const { return borders; }
  void setBorders(const QMap<CardinalDir, BorderPtr> &borders) { this->borders = borders; }
  void setBorder(CardinalDir dir, const QColor &color, bool preview = false);

  void paint(QPainter &painter);

private:
  void updateBorders();

  QRect rect;
  QColor color, previewColor;
  QMap<CardinalDir, BorderPtr> borders;
};

QDataStream &operator<<(QDataStream &stream, const Field &field);
QDataStream &operator>>(QDataStream &stream, Field &field);
QDataStream &operator<<(QDataStream &stream, const Border &border);
QDataStream &operator>>(QDataStream &stream, Border &border);

#endif // SLD_FIELD_H
