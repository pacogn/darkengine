cmake_minimum_required(VERSION 3.10.0)
project(SoftwareRenderer VERSION 0.1.0)

message("Processing " ${PROJECT_NAME})

# Add Dependencies
#--------------------------------------
include("dependencies/MindShake/mindshake_flags.cmake")
add_subdirectory("dependencies/minifb" EXCLUDE_FROM_ALL)
add_subdirectory("dependencies/MindShake")

# For all projects
#--------------------------------------
link_libraries(minifb)
link_libraries(MindShake)

include_directories(src)
include_directories(dependencies)

# Avoid RelWithDebInfo and MinSizeRel
#--------------------------------------
set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)

# Define Release by default
#--------------------------------------
message("CMAKE_BUILD_TYPE: " ${CMAKE_BUILD_TYPE})
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
    message(STATUS "Build type not specified: Use Release by default")
endif(NOT CMAKE_BUILD_TYPE)

# engine library
#--------------------------------------
set(SRC_ENGINE_FILES
    src/engine/CCamera.cpp
    src/engine/CCamera.h
    src/engine/CMesh.cpp
    src/engine/CMesh.h
    src/engine/CRenderer.cpp
    src/engine/CRenderer.h
    src/engine/CSceneNode.cpp
    src/engine/CSceneNode.h
    src/engine/CWindow.cpp
    src/engine/CWindow.h
)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/src" FILES ${SRC_ENGINE_FILES})

add_library(engine STATIC
    ${SRC_ENGINE_FILES}
)
target_include_directories(engine PRIVATE src/engine)
link_libraries(engine)

# Set output directory
#--------------------------------------
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin)

# Exercise 1
#--------------------------------------
set(SRC_EXERCISE_1_FILES
    src/exercise1/main.cpp
    src/exercise1/Stars.h
    src/exercise1/Stars.cpp
)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/src/exercise1" FILES ${SRC_EXERCISE_1_FILES})

add_executable(Exercise1 
    ${SRC_EXERCISE_1_FILES}
)
target_include_directories(Exercise1 PRIVATE src/exercise1)

# Asteroids
#--------------------------------------
set(SRC_ASTEROIDS_FILES
    src/asteroids/main.cpp
    src/asteroids/Asteroids.h
    src/asteroids/Asteroids.cpp
)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/src/asteroids" FILES ${SRC_ASTEROIDS_FILES})

add_executable(Asteroids
    ${SRC_ASTEROIDS_FILES}
)
target_include_directories(Asteroids PRIVATE src/asteroids)

# Organize Visual Studio Solution Folders
#--------------------------------------
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(TARGET MindShake PROPERTY FOLDER "Libs")
set_property(TARGET minifb PROPERTY FOLDER "Libs")
set_property(TARGET engine PROPERTY FOLDER "Libs")
set_property(TARGET Exercise1 PROPERTY FOLDER "Exercises")
set_property(TARGET Asteroids PROPERTY FOLDER "Exercises")
