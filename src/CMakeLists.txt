SET(NAME sld)

ADD_EXECUTABLE(
  ${NAME}

  main.cpp

  Util.h
  Util.cpp

  MainWindow.h
  MainWindow.cpp

  Grid.h
  Grid.cpp

  Border.h
  Border.cpp

  Field.h
  Field.cpp

  Toolbox.h
  Toolbox.cpp

  ColorButton.h
  ColorButton.cpp
  ColorWidget.h
  ColorWidget.cpp
  )

QT5_USE_MODULES(${NAME} Core Gui Widgets)
