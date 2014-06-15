#ifndef SLD_FIELD_H
#define SLD_FIELD_H

#include <QMap>
#include <QRect>
#include <QColor>
#include <QDataStream>

#include <memory>

class QPainter;

enum class CardinalDir : int {
  North,
  South,
  West,
  East
};

class Border {
public:
  Border() : color(Qt::transparent), previewColor(QColor()), active(false) { }

  QRect rect;
  QColor color, previewColor;
  bool active;
};

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
  void tryDetectBorder(const QPoint &pos, const QColor &color,
                       bool preview = false);

  const QMap<CardinalDir, Border> &getBorders() const { return borders; }
  void setBorders(const QMap<CardinalDir, Border> &borders) { this->borders = borders; }

  void paint(QPainter &painter);

private:
  void updateBorders();

  QRect rect;
  QColor color, previewColor;
  QMap<CardinalDir, Border> borders;
};

QDataStream &operator<<(QDataStream &stream, const Field &field);
QDataStream &operator>>(QDataStream &stream, Field &field);
QDataStream &operator<<(QDataStream &stream, const Border &border);
QDataStream &operator>>(QDataStream &stream, Border &border);

#endif // SLD_FIELD_H
