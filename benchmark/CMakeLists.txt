# This library organize the operations provided by
# officecontrol library together into some benchmark test option.
# The test will be abstract into three level.
# 1. operation.
#   Here operation have same meaning with the word's literal meaning.
#   (provided by officecontrol)
# 2. workload.
#   workload is defined as a class of similar operation.
#   the operations in a same workload may have different actions,
#   but they share the same object to operate on.
#   Or they have different object to operate on but are same action.
#   like start libreoffice writer, start libreoffice calc, start libreoffice impress,
#   all these will be classified into start app workload.
#   another example is insert characters, delete, copy, paste text content of a doc type document,
#   these will be classified into writing workload.
# 3. benchmark.
#   benchmark is defined as set of workload which construct an apply scenario.
# Developer can further create benchmark more
cmake_minimum_required(VERSION 3.10)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# set fot Qt Macro, cause used QObject
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_PREFIX_PATH /home/user/Qt/5.15.2/gcc_64)

set(LIBREOFFICESDKCPLUSHEADER /usr/include/libreoffice)
set(LIBREOFFICESDKUNOHEADER /home/user/Documents/libreofficeSDKoutput/libreoffice6.4_sdk/LINUXexample.out/inc/)

if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-fPIC -Wall -Wextra -pedantic)
endif()

# add preprocessor Macro
add_definitions(-DUNX -DGCC -DLINUX -DCPPU_ENV=gcc3)
add_compile_options(-fPIC -Wall -Wextra -pedantic)

# find library
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)

# prepare for compile, find dependency lib
find_library(REGLO_LIB NAMES libreglo.so PATHS /usr/lib/libreoffice/program/)
find_library(UNOIDLLO_LIB NAMES libunoidllo.so PATHS /usr/lib/libreoffice/program/)
find_library(XMLREADERLO_LIB NAMES libxmlreaderlo.so PATHS /usr/lib/libreoffice/program/)
find_library(UNO_CPPUHELPER_LIB NAMES libuno_cppuhelpergcc3.so PATHS /usr/lib/libreoffice/sdk/lib/)
find_library(UNO_CPPU_LIB NAMES libuno_cppu.so PATHS /usr/lib/libreoffice/sdk/lib/)
find_library(UNO_SALHELPER_LIB NAMES libuno_salhelpergcc3.so PATHS /usr/lib/libreoffice/sdk/lib)
find_library(UNO_SAL_LIB NAMES libuno_sal.so PATHS /usr/lib/libreoffice/sdk/lib/)
link_directories(/usr/lib/libreoffice/sdk/lib/)
link_directories(/usr/lib/libreoffice/program/)
link_directories(/usr/lib/libreoffice/)

# compile library
add_library(benchmark SHARED
    benchmark.h
    benchmark.cxx
    benchoffice.cxx
    officecontrol.h
    officecontrol.cxx
    writercontrol.cxx
    calccontrol.cxx
    impresscontrol.cxx)

target_include_directories(benchmark
                           INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
                           PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
                           PRIVATE ${LIBREOFFICESDKCPLUSHEADER}
                           PRIVATE ${LIBREOFFICESDKUNOHEADER}
                           PRIVATE ${CMAKE_PREFIX_PATH}
                           )
target_link_libraries(benchmark PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(benchmark PRIVATE Qt${QT_VERSION_MAJOR}::Core)

target_link_libraries(benchmark PUBLIC ${UNO_CPPUHELPER_LIB})
target_link_libraries(benchmark PUBLIC ${UNO_CPPU_LIB})
target_link_libraries(benchmark PUBLIC ${UNO_SALHELPER_LIB})
target_link_libraries(benchmark PUBLIC ${UNO_SAL_LIB})
target_link_libraries(benchmark PUBLIC ${REGLO_LIB})
target_link_libraries(benchmark PUBLIC ${UNOIDLLO_LIB})
target_link_libraries(benchmark PUBLIC ${XMLREADERLO_LIB})

install(TARGETS benchmark DESTINATION lib)
install(FILES benchmark.h DESTINATION include)
