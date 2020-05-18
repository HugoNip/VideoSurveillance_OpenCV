cmake_minimum_required(VERSION 3.0)
project(c08)

set(CMAKE_CXX_STANDARD 11)

# Requires OpenCV
find_package(OpenCV 4.0.0 REQUIRED)
message("OpenCV version: ${OpenCV_VERSION}")

include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIB_DIR})

add_executable(frameDifferencing frameDifferencing.cpp)
target_link_libraries(frameDifferencing ${OpenCV_LIBS})

add_executable(backgroundSubtraction backgroundSubtraction.cpp)
target_link_libraries(backgroundSubtraction ${OpenCV_LIBS})

add_executable(c08 main.cpp)