## AUTHOR: 'WANDEX/clbrd'
## Cmake conf which uses modern cmake targets approach & per target properties.
## Compiles target which uses Qt sources as separate static library.
##
## Per target properties:
## AUTOMOC, AUTOUIC instead of obsolete & de facto standard approach.
## Old approach used by nearly everyone across the web is obsolete:
##  1. Pollutes build directory.
##  2. Increases build times as unneeded properties are added to all targets.
##  3. Which leads to excessive/unneeded code generation by the Qt framework.

set(CLBRD_UI_FILES mainwindow.ui)

target_sources(clbrd_src
  PUBLIC FILE_SET headers TYPE HEADERS FILES
    ui.hpp
    keys.hpp
    mainwindow.hpp
  PRIVATE
    ${CLBRD_UI_FILES} # adding them here triggers AUTOUIC
    ui.cpp
    keys.cpp
    mainwindow.cpp
)
target_link_libraries(clbrd_src PRIVATE clbrd_deps INTERFACE clbrd_dev)

set_target_properties(clbrd_src PROPERTIES
  AUTOMOC ON # => Q_OBJECT
  AUTOUIC ON # => find -> generate: *.ui -> ui_*.h
  LINKER_LANGUAGE CXX
)

qt_add_executable(clbrd_app main.cpp)
target_link_libraries(clbrd_app PRIVATE clbrd_src clbrd_deps)

set_target_properties(clbrd_app PROPERTIES
  MACOSX_BUNDLE_GUI_IDENTIFIER org.wndx.clbrd
  MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
  MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
  MACOSX_BUNDLE TRUE
  WIN32_EXECUTABLE TRUE
)

qt_add_translations(clbrd_app
  SOURCES
    mainwindow.cpp
    ${CLBRD_UI_FILES} # adding them here triggers AUTOUIC
  TS_FILES
    i18n/clbrd_en_US.ts
    i18n/clbrd_ru_RU.ts
    i18n/clbrd_zh_CN.ts
)
