cmake_minimum_required(VERSION 2.8)

project(DiadocApi)

add_definitions(-DUNICODE)
add_definitions(-D_UNICODE)

add_subdirectory("third-party")

include_directories(
	"${CMAKE_CURRENT_SOURCE_DIR}/third-party/include/"
)

add_subdirectory("src")
