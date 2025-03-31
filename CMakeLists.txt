cmake_minimum_required(VERSION 3.10)  # Se recomienda usar CMake 3.10 o superior
project(EvaluadorDeExpresiones VERSION 1.0 LANGUAGES CXX)  # Nombre del proyecto

set(CMAKE_CXX_STANDARD 23)  
set(CMAKE_CXX_STANDARD_REQUIRED OUTPUT_NAME)  

set(SOURCES 
src/EvaluadorDeExpresiones.cpp 
)

# Agrega el ejecutable
add_executable(EvaluadorDeExpresiones ${SOURCES} src/main.cpp)
target_link_libraries(EvaluadorDeExpresiones PRIVATE stdc++exp)  # Enlaza la librería de filesystem

# Setup Catch2 for testing
Include(FetchContent)
include_directories(includes)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.4.0 # or a later release
)

FetchContent_MakeAvailable(Catch2)
message(STATUS "Catch2 version: ${Catch2_VERSION}")
add_executable(tests ${SOURCES} tests/test.cpp )  # Asegúrate de listar todos tus archivos fuente aquí
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain stdc++exp)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)
catch_discover_tests(tests)


# Habilitar pruebas en CMake
# enable_testing()
# add_test(NAME Evaluador_Tests COMMAND tests)
