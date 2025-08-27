cmake_minimum_required(VERSION 3.10)
project(minigb C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package(raylib REQUIRED)

add_library(minigb_core SHARED
    source/minigb_core.cpp
)
target_link_libraries(minigb_core PRIVATE raylib m pthread)

set_target_properties(minigb_core PROPERTIES PREFIX "" SUFFIX ".so")

add_custom_command(TARGET minigb_core POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
            $<TARGET_FILE:minigb_core>
            ${CMAKE_CURRENT_BINARY_DIR}
)
