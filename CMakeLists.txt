cmake_minimum_required(VERSION 3.21)
project(MixEditor VERSION 1.0.0)

if (NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "GEODE_SDK não definido. Usa o build-geode-mod ou configura o SDK.")
else()
    message(STATUS "Geode encontrado: $ENV{GEODE_SDK}")
endif()

add_subdirectory($ENV{GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode)
setup_geode_mod()
