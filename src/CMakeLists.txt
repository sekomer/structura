cmake_minimum_required(VERSION 3.0)

project(Structura)

set(CMAKE_C_STANDARD 99)

include_directories(${PROJECT_SOURCE_DIR}/include)

# Add all the source files
set(SOURCES
    structura.c
    ring.c
    stack.c
    linked.c
)

# add headers from include directory
file(GLOB HEADERS ${PROJECT_SOURCE_DIR}/include/*.h)


# Create a library with all the source files
add_library(structura ${SOURCES} ${HEADERS})

# Link the Python library
find_package(Python REQUIRED COMPONENTS Interpreter Development)
target_include_directories(structura PUBLIC ${Python_INCLUDE_DIRS})
target_link_libraries(structura ${Python_LIBRARIES})