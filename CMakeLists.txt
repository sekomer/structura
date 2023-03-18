project(Structura)
set(CMAKE_C_STANDARD 99)
cmake_minimum_required(VERSION 3.0)

add_subdirectory(src)
include_directories(include)

find_package(Python REQUIRED COMPONENTS Interpreter Development)
include_directories(${Python_INCLUDE_DIRS})

include_directories(/usr/include/python3.8)

add_library(_structura SHARED 
            src/structura.c 
            src/ring.c 
            src/stack.c 
            src/linked.c
            src/hashmap.c
            src/priority.c)

set_target_properties(
    structura
    PROPERTIES
        PREFIX ""
        OUTPUT_NAME "structura"
        LINKER_LANGUAGE C
)