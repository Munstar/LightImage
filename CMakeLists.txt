cmake_minimum_required(VERSION 2.8)
project(LightImage)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

include_directories(include)

set(uis app/res/mainwindow.ui
        app/res/mirrordialog.ui
        app/res/rotatedialog.ui
        app/res/scaledialog.ui
        app/res/clipdialog.ui
        app/res/movedialog.ui)

set(rcs app/res/lightimage.qrc)

QT5_WRAP_UI(ui_srcs ${uis})
QT5_ADD_RESOURCES(rc_srcs ${rcs})

set(link_libs Qt5::Core Qt5::Widgets)

set(qt_source       app/include/mainwindow.h
                    app/src/mainwindow.cpp
                    app/src/main.cpp
                    app/include/util.hpp
                    app/include/mirrordialog.h
                    app/src/mirrordialog.cpp
                    app/include/rotatedialog.h
                    app/src/rotatedialog.cpp
                    app/include/scaledialog.h
                    app/src/scaledialog.cpp
                    app/include/imagescene.h
                    app/src/imagescene.cpp
                    app/include/clipdialog.h
                    app/src/clipdialog.cpp
                    app/include/movedialog.h
                    app/src/movedialog.cpp
)

set(core_source     modules/core/include/types.h
                    modules/core/include/core.hpp
                    modules/core/include/point.hpp
                    modules/core/include/matrix.hpp
                    modules/core/include/vect.hpp
                    modules/core/include/error.hpp
                    modules/io/include/io.h
                    modules/io/src/io.cpp
                    modules/core/include/image.h
                    modules/core/src/image.cpp
                    modules/histogram/include/histogram.h
                    modules/histogram/src/histogram.cpp
                    modules/geometry_transform/include/geometry.h
                    modules/geometry_transform/src/geometry.cpp
                    modules/frequency_domain_transform/include/dft.h
                    modules/frequency_domain_transform/src/dft.cpp
                    modules/frequency_domain_transform/include/dct.h
                    modules/frequency_domain_transform/src/dct.cpp
                    modules/color/include/color.h
                    modules/color/src/color.cpp
                    modules/filter/include/filter.h
                    modules/filter/src/filter.cpp
 )
add_executable(LightImage ${qt_source} ${ui_srcs} ${core_source} ${rc_srcs})
target_link_libraries(LightImage ${link_libs})