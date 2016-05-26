cmake_minimum_required(VERSION 2.8)

project(DiadocApi)

add_definitions(-DUNICODE)
add_definitions(-D_UNICODE)
add_definitions(-DWIN32_LEAN_AND_MEAN)

add_subdirectory("third-party")

set (GOOGLE_PROTOBUF_PATH "${CMAKE_CURRENT_SOURCE_DIR}/third-party/protobuf/")
include_directories(
	"${GOOGLE_PROTOBUF_PATH}/include/"
	"${GOOGLE_PROTOBUF_PATH}/vsprojects/"
)
