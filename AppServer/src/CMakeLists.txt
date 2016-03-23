cmake_minimum_required(VERSION 2.8.7)
project(AppServer)


#sets compile flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++11 -O0 -coverage")

#adds the ldflags needed to link rocksdb
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lrt -lsnappy -lgflags -lz -lbz2")


#adds the source and header files recursively
file(GLOB_RECURSE SOURCES "./*.cpp" "./*.c")
file(GLOB_RECURSE HEADERS "./*.h")

#adds directories with headers recursively
set (DIRS "")
foreach (_header ${HEADERS})
    get_filename_component(_dir ${_header} PATH)
    list (APPEND DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES DIRS)
include_directories(${DIRS})

#includes directories without headers
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/third_party/rocksdb/include)


add_executable (AppServer ${SOURCES})
set_target_properties(AppServer PROPERTIES LINKER_LANGUAGE CXX)


#Adds static libraries
add_library(rocksdb STATIC IMPORTED)
set_property(TARGET rocksdb PROPERTY IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/third_party/rocksdb/librocksdb.a)

include_directories(LIBZ)
add_library(LIBZ STATIC IMPORTED)
set_property(TARGET LIBZ PROPERTY IMPORTED_LOCATION /usr/lib/x86_64-linux-gnu/libz.a)

include_directories(SNAPPY)
add_library(SNAPPY STATIC IMPORTED)
set_property(TARGET SNAPPY PROPERTY IMPORTED_LOCATION /usr/lib/libsnappy.a)

include_directories(BZ2)
add_library(BZ2 STATIC IMPORTED)
set_property(TARGET BZ2 PROPERTY IMPORTED_LOCATION /usr/lib/x86_64-linux-gnu/libbz2.a)


target_link_libraries(AppServer rocksdb LIBZ SNAPPY BZ2)
