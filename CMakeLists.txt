cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add debuggin symbols to the build
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "-g")

project(Game)

# Include directories for headers
include_directories(
    lib/raylib/raylib/include
    lib/box2d/include/box2d
    lib/loadtmx
    lib/loadtmx/tinyxml2
    Classes/src
)

# Link library directories
link_directories(
    lib/raylib/raylib
    lib/box2d/src
    Classes/build
)

# Add external libraries
add_library(raylib STATIC IMPORTED)
set_target_properties(raylib PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/raylib/raylib/libraylib.a)

add_library(box2d STATIC IMPORTED)
set_target_properties(box2d PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/box2d/src/libbox2d.a)

# add_library(loadtmx STATIC IMPORTED)
# set_target_properties

add_library(tinyxml2 STATIC IMPORTED)
set_target_properties(tinyxml2 PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/loadtmx/tinyxml2/libtinyxml2.a)

# Add the main executable
add_executable(main src/main.cpp)

# Link the static libraries and macOS frameworks
target_link_libraries(main
    raylib
    box2d
    tinyxml2
    ${CMAKE_SOURCE_DIR}/Classes/build/libSprite.a
    ${CMAKE_SOURCE_DIR}/Classes/build/libAnimation.a
    ${CMAKE_SOURCE_DIR}/Classes/build/libNode.a
    ${CMAKE_SOURCE_DIR}/Classes/build/libTile.a
    ${CMAKE_SOURCE_DIR}/Classes/build/libTileGrid.a
    ${CMAKE_SOURCE_DIR}/Classes/build/libTileMapLayer.a
    ${CMAKE_SOURCE_DIR}/Classes/build/libTilePalette.a
    ${CMAKE_SOURCE_DIR}/Classes/build/libGridBrushTool.a
    ${CMAKE_SOURCE_DIR}/Classes/build/libCursorController.a
    "-framework Cocoa"
    "-framework IOKit"
    "-framework CoreFoundation"
)