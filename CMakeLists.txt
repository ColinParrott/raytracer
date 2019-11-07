cmake_minimum_required(VERSION 2.8)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 11)

project("Ray Tracer" C CXX)

include_directories(
parsers
math)

file (GLOB rapidjson_headers
parsers/rapidjson/*.h
)

file (GLOB source
main/*.cpp
core/*.cpp
cameras/*.cpp
lights/*.cpp
shapes/*.cpp
materials/*.cpp
)

find_package(OpenMP REQUIRED)
#raytracer executable
add_executable(raytracer ${source} math/geometry.h ${rapidjson_headers})

#json example executable
add_executable(jsonexample examples/jsonExample.cpp ${rapidjson_headers})

#vector example executable
add_executable(vectorexample examples/vecMatrixExample.cpp math/geometry.h)

target_compile_options(raytracer PRIVATE -Wall ${OpenMP_CXX_FLAGS})
target_link_libraries(raytracer PRIVATE ${OpenMP_CXX_FLAGS})