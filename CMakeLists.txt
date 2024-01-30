cmake_minimum_required(VERSION 3.24)
project(DjikstraVisualizer)

set(CMAKE_CXX_STANDARD 17)

add_executable(DjikstraVisualizer main.cpp DjikstraAlg.cpp dropDownMenu.cpp Graph.cpp node.cpp Edge.cpp Checkbox.cpp)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(c:/SFML/include/SFML)
target_link_libraries(DjikstraVisualizer sfml-system sfml-window sfml-graphics sfml-audio)


