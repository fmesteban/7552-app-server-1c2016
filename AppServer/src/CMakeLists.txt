#Define macro that lists the subdirectories
MACRO(SUBDIRLIST result curdir)
  FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
  SET(dirlist "")
  FOREACH(child ${children})
    IF(IS_DIRECTORY ${curdir}/${child})
        LIST(APPEND dirlist ${child})
    ENDIF()
  ENDFOREACH()
  SET(${result} ${dirlist})
ENDMACRO()


cmake_minimum_required(VERSION 2.8.7)
project(AppServer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O0 -Wall -coverage")
 
file(GLOB_RECURSE SOURCES "./*.cpp" "./*.c")
 
#List the subdirectories
SUBDIRLIST(SUBDIRS ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(${SUBDIRS})
 
add_executable(AppServer ${SOURCES})