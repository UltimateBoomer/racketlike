cmake_minimum_required(VERSION 3.22)

project(
  racketlike
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(CMAKE_CXX_FLAGS_DEBUG
    "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -Wall")
endif()

function(add_sources target_name source_dir)
  file(GLOB_RECURSE sources "${source_dir}/*.cc")
  target_sources(${target_name} PRIVATE ${sources})
endfunction()

add_executable(${PROJECT_NAME})

add_sources(${PROJECT_NAME} "${CMAKE_CURRENT_SOURCE_DIR}/src")

target_include_directories(${PROJECT_NAME} PRIVATE include)

target_link_libraries(${PROJECT_NAME})
