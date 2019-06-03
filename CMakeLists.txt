cmake_minimum_required(VERSION 3.5)
project(bacons_law)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE  src/parser.cpp
            src/mylib.cpp
            src/graph.cpp)

set(INCLUDE include/parser.h
            include/mylib.h
            include/graph.h)

if(MINGW)
    set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} -static-libstdc++)
endif()

add_executable(bacons_law   main.cpp
                            ${SOURCE}
                            ${INCLUDE})