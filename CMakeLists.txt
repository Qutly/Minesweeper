cmake_minimum_required(VERSION 3.24)
project(PO)

set(CMAKE_CXX_STANDARD 17)
set(EXECUTABLE_NAME "PO")

add_executable(PO src/main.cpp src/Board.cpp inc/Board.h src/BoardTextView.cpp inc/BoardTextView.h inc/TextController.h src/TextController.cpp inc/SFMLView.h src/SFMLView.cpp src/SFMLController.cpp inc/SFMLController.h)

if(UNIX)
    set (CMAKE_PREFIX_PATH "/usr/lib/x86_64-linux-gnu/cmake/SFML" ${CMAKE_PREFIX_PATH})
endif(UNIX)

find_package(SFML 2 COMPONENTS graphics audio REQUIRED)
target_link_libraries(PO sfml-graphics sfml-audio)