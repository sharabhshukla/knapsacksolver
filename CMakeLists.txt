cmake_minimum_required(VERSION 3.15)
project(knapsacksolver)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Detect pixi/conda environment and set PKG_CONFIG_PATH
if(DEFINED ENV{CONDA_PREFIX})
    set(ENV{PKG_CONFIG_PATH} "$ENV{CONDA_PREFIX}/lib/pkgconfig:$ENV{PKG_CONFIG_PATH}")
    message(STATUS "Using CONDA_PREFIX: $ENV{CONDA_PREFIX}")
endif()

# Also check for .pixi directory (for direct CLion builds)
if(EXISTS "${CMAKE_SOURCE_DIR}/.pixi/envs/default")
    set(ENV{PKG_CONFIG_PATH} "${CMAKE_SOURCE_DIR}/.pixi/envs/default/lib/pkgconfig:$ENV{PKG_CONFIG_PATH}")
    message(STATUS "Found .pixi environment, using: ${CMAKE_SOURCE_DIR}/.pixi/envs/default")
endif()

include(FetchContent)

FetchContent_Declare(
    pybind11
    GIT_REPOSITORY https://github.com/pybind/pybind11
    GIT_TAG v2.11.1
)
FetchContent_MakeAvailable(pybind11)

# Use pkg-config to find Coin-OR libraries
find_package(PkgConfig REQUIRED)

# Find Clp via pkg-config
pkg_check_modules(Clp REQUIRED IMPORTED_TARGET GLOBAL clp)
add_library(Coin::Clp ALIAS PkgConfig::Clp)
add_library(Coin::ClpSolver ALIAS PkgConfig::Clp)

# Find OsiClp via pkg-config
pkg_check_modules(OsiClp REQUIRED IMPORTED_TARGET GLOBAL osi-clp)
add_library(Coin::OsiClp ALIAS PkgConfig::OsiClp)

# Find Cbc via pkg-config
pkg_check_modules(Cbc REQUIRED IMPORTED_TARGET GLOBAL cbc)
add_library(Coin::Cbc ALIAS PkgConfig::Cbc)
add_library(Coin::CbcSolver ALIAS PkgConfig::Cbc)

# Find OsiCbc via pkg-config
pkg_check_modules(OsiCbc REQUIRED IMPORTED_TARGET GLOBAL osi-cbc)
add_library(Coin::OsiCbc ALIAS PkgConfig::OsiCbc)

# Find HiGHS via pkg-config
pkg_check_modules(HIGHS IMPORTED_TARGET GLOBAL highs)
if(HIGHS_FOUND)
    add_library(HIGHS::HIGHS ALIAS PkgConfig::HIGHS)
    message(STATUS "Found HiGHS: ${HIGHS_VERSION}")
endif()

# Find SCIP via pkg-config
pkg_check_modules(SCIP IMPORTED_TARGET GLOBAL scip)
if(SCIP_FOUND)
    add_library(libscip ALIAS PkgConfig::SCIP)
    message(STATUS "Found SCIP: ${SCIP_VERSION}")
endif()

# Now find OR-Tools
find_package(ortools REQUIRED CONFIG)

# Create Python module
pybind11_add_module(cknapsacksolver
    src/cpp/kmodel.cpp
    src/cpp/kmodel.h
    src/python_bindings.cpp
)

target_include_directories(cknapsacksolver PRIVATE src/cpp)
target_link_libraries(cknapsacksolver PRIVATE ortools::ortools)

# Install the module to the knapsacksolver package
install(TARGETS cknapsacksolver LIBRARY DESTINATION knapsacksolver)
