## src

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Network)
find_package(QT NAMES Qt6) # => populate QT_VERSION variables!

target_link_libraries(clbrd_deps PUBLIC Qt6::Core Qt6::Widgets Qt6::Network)

add_subdirectory(common)
add_subdirectory(client)
add_subdirectory(daemon)

