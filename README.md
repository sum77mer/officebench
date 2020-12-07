### OfficeBenchMark

## how to compile

1. install libreoffice SDK
$apt search libreoffice-dev
$sudo apt install libreoffice-dev
$sudo apt install libreoffice-dev-common
$sudo apt install libreoffice-dev-doc

2. install Qt
download qt-unified-linux-x64-x.x.x-online.run(mine 4.0.0)

3. edit ./CMakeLists.txt:
set(CMAKE_PREFIX_PATH /home/user/Qt/5.15.2/gcc_64)

4. edit ./benchmark/CMakeLists.txt:
set(CMAKE_PREFIX_PATH /home/user/Qt/5.15.2/gcc_64)
set(LIBREOFFICESDKCPLUSHEADER /usr/include/libreoffice)
set(LIBREOFFICESDKUNOHEADER /home/user/Documents/libreofficeSDKoutput/libreoffice6.4_sdk/LINUXexample.out/inc/)

5. and lib and header path if your libreoffice sdk install path is different:
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

6. compile
$mkdir build
$cmake ../
$cmake --build .

7. run
$./officebenchmark

## install
(There's dependency problem, so the installation won't work)
after cmake, execute cpack to generate a install pack
$cpack
$./officebenchmark--Linux.sh


