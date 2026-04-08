cmake_minimum_required(VERSION 3.20)
project(SortingVisualizer)

set(CMAKE_CXX_STANDARD 20)

set(SFML_ROOT "C:/libraries/SFML-3.0.2")
set(SFML_DIR "${SFML_ROOT}/lib/cmake/SFML")

find_package(SFML 3.0.2 REQUIRED COMPONENTS Graphics Audio Network System)

add_executable(SortingVisualizer main.cpp
        headers/Visualizer.cpp
        headers/Visualizer.h
        headers/Rectangle.cpp
        headers/Rectangle.h
        headers/Rectangles.cpp
        headers/Rectangles.h
        headers/SortingAlgorithm.cpp
        headers/SortingAlgorithm.h)

target_link_libraries(SortingVisualizer PRIVATE SFML::Graphics SFML::Audio SFML::Network SFML::System)

if (WIN32)
    add_custom_command(TARGET SortingVisualizer POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SFML_ROOT}/bin/sfml-system-d-3.dll" $<TARGET_FILE_DIR:SortingVisualizer>

            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SFML_ROOT}/bin/sfml-window-d-3.dll" $<TARGET_FILE_DIR:SortingVisualizer>

            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SFML_ROOT}/bin/sfml-graphics-d-3.dll" $<TARGET_FILE_DIR:SortingVisualizer>
    )
endif()