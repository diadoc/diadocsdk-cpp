cmake_minimum_required(VERSION 2.8)

project(DiadocApi)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_definitions(-DUNICODE)
add_definitions(-D_UNICODE)

add_subdirectory("third-party")

include_directories(
	"${CMAKE_CURRENT_SOURCE_DIR}/third-party/include/"
)

add_subdirectory("src")
