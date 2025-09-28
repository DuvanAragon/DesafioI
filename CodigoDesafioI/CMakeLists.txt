cmake_minimum_required(VERSION 3.16)

project(CodigoDesafioI LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_executable(CodigoDesafioI
  main.cpp
  compresion.h
  compresion.cpp
  utilidadesCadenas.h
  utilidadesCadenas.cpp
  utilidadesBytes.h
  utilidadesBytes.cpp
  manejoArchivos.h
  manejoArchivos.cpp
  encotrarRotacionClave.h
  encotrarRotacionClave.cpp
)
target_link_libraries(CodigoDesafioI Qt${QT_VERSION_MAJOR}::Core)

include(GNUInstallDirs)
install(TARGETS CodigoDesafioI
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
