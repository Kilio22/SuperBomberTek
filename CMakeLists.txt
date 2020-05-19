cmake_minimum_required(VERSION 3.11)

# set the project name & version
project(Bomberman VERSION 0.1)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

set(Irrlicht_DIR "${CMAKE_MODULE_PATH}/Irrlicht")

IF(WIN32)
        set(SFML_DIR "${CMAKE_MODULE_PATH}/SFML/lib/cmake/SFML")
ENDIF(WIN32)

# find packages (le .cmake dedans)
find_package(Irrlicht REQUIRED)
find_package(SFML 2.5 COMPONENTS system audio REQUIRED)

# add include directories
include_directories(include)
include_directories(include/Power-Ups)
include_directories(${Irrlicht_INCLUDE_DIRS})

# add the executable
#add_definitions("-Wall -g")
file(GLOB SRCS src/*.cpp)
file(GLOB SRCS_POWER src/Power-Ups/*.cpp)
add_executable(Bomberman ${SRCS} ${SRCS_POWER} )

target_link_libraries(Bomberman ${Irrlicht_LIBRARIES})
target_link_libraries(Bomberman sfml-graphics sfml-audio)