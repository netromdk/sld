SET(NAME sld)

ADD_EXECUTABLE(
  ${NAME}

  main.cpp

  MainWindow.h
  MainWindow.cpp

  Grid.h
  Grid.cpp

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
