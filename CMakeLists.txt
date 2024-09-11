cmake_minimum_required(VERSION 3.15...3.26)
project(${SKBUILD_PROJECT_NAME} LANGUAGES CXX)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# dependencies
file(
        DOWNLOAD
        https://github.com/cpm-cmake/CPM.cmake/releases/download/v0.40.2/CPM.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake
        EXPECTED_HASH SHA256=c8cdc32c03816538ce22781ed72964dc864b2a34a310d3b7104812a5ca2d835d
      )
      include(${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake)

CPMAddPackage(
        NAME ccronexpr
        GITHUB_REPOSITORY exander77/supertinycron
        GIT_TAG d808e3dc15b7bab574caee02f08fe1fc0182e444
)

set(PYBIND11_NEWPYTHON ON)
find_package(pybind11 CONFIG REQUIRED)

pybind11_add_module(_ccronexpr src/_ccronexpr.cpp)

target_link_libraries(_ccronexpr PRIVATE ccronexpr)

install(TARGETS _ccronexpr LIBRARY DESTINATION .)
