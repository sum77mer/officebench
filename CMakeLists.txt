cmake_minimum_required(VERSION 3.10)

project(officebenchmark VERSION 0.9 LANGUAGES CXX)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# set Qt Macro
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_PREFIX_PATH /home/user/Qt/5.15.2/gcc_64)

add_subdirectory(benchmark)
list(APPEND EXTRA_LIBS benchmark)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)

add_executable(officebenchmark
    main.cxx
  mainwindow.cxx
  mainwindow.h
  tabwidget.cxx
  tabwidget.h
  homewidget.cxx
  homewidget.h
  resultwidget.cxx
  resultwidget.h
  helpwidget.cxx
  helpwidget.h
  teststatuswidget.cxx
  teststatuswidget.h
  resultloadingwidget.cxx
  resultloadingwidget.h
  prepareforbenchmarkbutton.cxx
  prepareforbenchmarkbutton.h
  officebenchmark_data.h
  treemodel.h
  treemodel.cpp
  treeitem.h
  treeitem.cpp
)

target_link_libraries(officebenchmark PUBLIC benchmark)

target_link_libraries(officebenchmark PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(officebenchmark PRIVATE Qt${QT_VERSION_MAJOR}::Core)

# add the binary tree to the search path for include files
target_include_directories(officebenchmark PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )
# install
install(TARGETS officebenchmark DESTINATION bin)

include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
include(CPack)
