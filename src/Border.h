#ifndef SLD_BORDER_H
#define SLD_BORDER_H

#include <QRect>
#include <QColor>
#include <QDataStream>

#include <memory>

class QPainter;

class Border;
typedef std::shared_ptr<Border> BorderPtr;

class Border {
public:
  Border() : color(Qt::transparent), previewColor(QColor()), active(false) { }

  const QRect &getRect() const { return rect; }
  void setRect(const QRect &rect) { this->rect = rect; }

  bool isActive() const { return active; }
  void setActive(bool active) { this->active = active; }

  const QColor &getColor() const { return color; }
  void setColor(const QColor &color) { this->color = color; }
  void setPreviewColor(const QColor &color) { previewColor = color; }

  void paint(QPainter &painter);

private:
  QRect rect;
  QColor color, previewColor;
  bool active;
};

QDataStream &operator<<(QDataStream &stream, const Border &border);
QDataStream &operator>>(QDataStream &stream, Border &border);

#endif // SLD_BORDER_H
