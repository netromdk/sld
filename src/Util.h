#ifndef SLD_UTIL_H
#define SLD_UTIL_H

#include "CardinalDir.h"

class QWidget;

class Util {
public:
  static void centerWidget(QWidget *widget);
  static CardinalDir oppositeDir(CardinalDir dir);
};

#endif // SLD_UTIL_H
