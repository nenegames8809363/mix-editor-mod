cmake_minimum_required(VERSION 3.21)
project(MixEditor VERSION 1.0.0)

file(GLOB SOURCES src/*.cpp)

if (NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "GEODE_SDK não definido. Instala o SDK ou usa o Actions.")
endif()

include($ENV{GEODE_SDK}/cmake/geode-sdk.cmake)
setup_geode_mod(${SOURCES})
