#Gets current directory name
get_filename_component(CurrDir ${CMAKE_CURRENT_SOURCE_DIR} NAME)

#Adds c source files as libraries
file(GLOB c_files "./*.c")
foreach(file ${c_files})
    ADD_LIBRARY(${CurrDir} ${file})
endforeach()

#Adds cpp source files as libraries
file(GLOB c_files "./*.cpp")
foreach(file ${c_files})
    ADD_LIBRARY(${CurrDir} ${file})
endforeach()

