#include <QWidget>
#include <QApplication>
#include <QDesktopWidget>

#include "Util.h"

void Util::centerWidget(QWidget *widget) {
  widget->move(QApplication::desktop()->screen()->rect().center()
               - widget->rect().center());
}
