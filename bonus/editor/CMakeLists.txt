cmake_minimum_required(VERSION 3.11)

# set the project name & version
project(generator VERSION 0.1)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

IF(WIN32)
        set(SFML_DIR "${CMAKE_MODULE_PATH}/SFML/lib/cmake/SFML")
ENDIF(WIN32)

# find packages (le .cmake dedans)
find_package(SFML 2.5 COMPONENTS system graphics window audio REQUIRED)

# add include directories
include_directories(include)

# add the executable
# add_definitions("-Wall -g")
file(GLOB SRCS src/*.cpp)
add_executable(generator ${SRCS})

target_link_libraries(generator sfml-system sfml-graphics sfml-window sfml-audio)