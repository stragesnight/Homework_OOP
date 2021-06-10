# cache string for directory containing source files
set(SRC_DIR "./" CACHE STRING "some__cache__for__user__input")
# variable project name
set(PROJ_NAME StudentGrades)

cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD, 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(${PROJ_NAME})

# add files to project
file(GLOB SOURCE_FILES ${SRC_DIR}/*.cpp)
file(GLOB HEADER_FILES ${SRC_DIR}/*.h)

foreach(srcfile ${SOURCE_FILES})
    get_filename_component(filename ${srcfile} NAME_WE)
    if(NOT filename STREQUAL "main")
        add_library(${filename} ${srcfile})
        list(APPEND LIB_LIST ${filename})
        message("added static library ${filename}")
    endif()
endforeach(srcfile ${SOURCE_FILES})

include_directories(${SRC_DIR}/)

add_executable(${PROJ_NAME} ${SRC_DIR}/main.cpp)

target_link_libraries(${PROJ_NAME} PUBLIC ${LIB_LIST})
