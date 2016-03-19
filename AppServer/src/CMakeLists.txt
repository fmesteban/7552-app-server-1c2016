cmake_minimum_required(VERSION 2.8.7)
project(AppServer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -Wall -coverage")
 
add_definitions( -Wall -O3 -I".*" )

file(GLOB_RECURSE SOURCES "./*.cpp" "./*.c")
file(GLOB_RECURSE HEADERS "./*.h")

set (DIRS "")
foreach (_header ${HEADERS})
    get_filename_component(_dir ${_header} PATH)
    list (APPEND DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES DIRS)

include_directories(${DIRS})
add_executable (AppServer ${SOURCES})
set_target_properties(AppServer PROPERTIES LINKER_LANGUAGE CXX)