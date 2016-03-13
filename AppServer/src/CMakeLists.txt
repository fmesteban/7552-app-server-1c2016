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

#Define the minimum cmake version required
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
#Define the project name
PROJECT(AppServer)

#Include the current directory
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

#List the subdirectories
SUBDIRLIST(SUBDIRS ${CMAKE_CURRENT_SOURCE_DIR})

#Adds the subdirectories sources as libraries
FOREACH(subdir ${SUBDIRS})
	INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/${subdir})
	ADD_SUBDIRECTORY(${subdir})
	SET(EXTRA_LIBS ${EXTRA_LIBS} ${subdir})
ENDFOREACH()

#Adds the exec and links with the libraries
ADD_EXECUTABLE(AppServer websocket_chat.c)
TARGET_LINK_LIBRARIES(AppServer ${EXTRA_LIBS})
