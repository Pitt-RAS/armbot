cmake_minimum_required(VERSION 3.0)

project(brain C)

find_library(WIRINGPI_LIB wiringPI REQUIRED)

# set compile flags
set(cflags -Wall)
if (CMAKE_BUILD_TYPE EQUAL Debug)
    set(cflags ${cflags} -Og -g)
elseif (CMAKE_BUILD_TYPE EQUAL Release)
    set(cflags ${cflags} -O2)
endif()

# add files to project
file(GLOB sources src/*.c)
file(GLOB headers src/*.h)
add_executable(${PROJECT_NAME} ${sources} ${headers})

target_compile_options(${PROJECT_NAME} PRIVATE ${cflags})
#target_link_libraries(${PROJECT_NAME} PRIVATE ${WIRINGPI_LIB})
