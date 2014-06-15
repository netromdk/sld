#include <QWidget>
#include <QApplication>
#include <QDesktopWidget>

#include "Util.h"

void Util::centerWidget(QWidget *widget) {
  widget->move(QApplication::desktop()->screen()->rect().center()
               - widget->rect().center());
}

CardinalDir Util::oppositeDir(CardinalDir dir) {
  switch (dir) {
  case CardinalDir::North:
    return CardinalDir::South;

  case CardinalDir::South:
    return CardinalDir::North;

  case CardinalDir::West:
    return CardinalDir::East;

  case CardinalDir::East:
    return CardinalDir::West;
  }
}
