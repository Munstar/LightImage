cmake_minimum_required(VERSION 2.8)
project(LightImage)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES    main.cpp
                    modules/core/include/types.h
                    modules/core/include/core.hpp
                    modules/core/include/point.hpp
                    modules/core/include/vect.hpp
                    modules/core/include/error.hpp
 )
add_executable(LightImage ${SOURCE_FILES})