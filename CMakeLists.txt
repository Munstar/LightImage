cmake_minimum_required(VERSION 2.8)
project(LightImage)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

set(link_libs Qt5::Core Qt5::Widgets)

set(SOURCE_FILES    main.cpp
                    modules/core/include/types.h
                    modules/core/include/core.hpp
                    modules/core/include/point.hpp
                    modules/core/include/matrix.hpp
                    modules/core/include/vect.hpp
                    modules/core/include/error.hpp
                    modules/io/include/io.h
                    modules/io/src/io.cpp
 )
add_executable(LightImage ${SOURCE_FILES})
target_link_libraries(LightImage ${link_libs})