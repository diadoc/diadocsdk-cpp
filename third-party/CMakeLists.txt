cmake_minimum_required(VERSION 2.8)

option(PROTOBUF_BUILD_SHARED_LIBS "Build the static library" OFF)
set(PROTOBUF_VERSION_TAG "2.6.1" CACHE STRING "Protobuf version tag from github")

set (GOOGLE_PROTOBUF_ARCHIVE_PATH "${CMAKE_CURRENT_BINARY_DIR}/protobuf-${PROTOBUF_VERSION_TAG}.tar.gz")
set (GOOGLE_PROTOBUF_EXTRACT_ARCHIVE_WORKING_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set (GOOGLE_PROTOBUF_EXTRACTED_ARCHIVE_PATH "${GOOGLE_PROTOBUF_EXTRACT_ARCHIVE_WORKING_DIR}/protobuf-${PROTOBUF_VERSION_TAG}/")
set (GOOGLE_PROTOBUF_SOURCE_PATH ${GOOGLE_PROTOBUF_EXTRACTED_ARCHIVE_PATH})
set (GOOGLE_PROTOBUF_INCLUDE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/include/google/protobuf/)

if (NOT EXISTS ${GOOGLE_PROTOBUF_SOURCE_PATH})
	if (NOT EXISTS ${GOOGLE_PROTOBUF_ARCHIVE_PATH})
		file(DOWNLOAD
			"https://github.com/google/protobuf/archive/v${PROTOBUF_VERSION_TAG}.tar.gz"
			${GOOGLE_PROTOBUF_ARCHIVE_PATH}
			SHOW_PROGRESS)
	endif()
	execute_process(
		COMMAND ${CMAKE_COMMAND} -E tar xvf ${GOOGLE_PROTOBUF_ARCHIVE_PATH}
		WORKING_DIRECTORY ${GOOGLE_PROTOBUF_EXTRACT_ARCHIVE_WORKING_DIR})
	if (NOT EXISTS ${GOOGLE_PROTOBUF_SOURCE_PATH})
		message(FATAL_ERROR "Please, check where protobuf was extracted")
	endif()
endif()

if (NOT EXISTS ${GOOGLE_PROTOBUF_INCLUDE_PATH})
	execute_process(
		COMMAND           "${GOOGLE_PROTOBUF_SOURCE_PATH}/vsprojects/extract_includes.bat"
		WORKING_DIRECTORY "${GOOGLE_PROTOBUF_SOURCE_PATH}/vsprojects/")
	file(COPY "${GOOGLE_PROTOBUF_SOURCE_PATH}/vsprojects/include" DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/")
	if (NOT EXISTS ${GOOGLE_PROTOBUF_INCLUDE_PATH})
		message(FATAL_ERROR "Please, check where protobuf include was copied")
	endif()
endif()

option(PROTOBUF_BUILD_SHARED_LIBS "Build the static library" OFF)
include_directories(
	"${GOOGLE_PROTOBUF_SOURCE_PATH}/src/"
	"${GOOGLE_PROTOBUF_SOURCE_PATH}/vsprojects/"
)

add_definitions("/wd4244 /wd4267 /wd4018 /wd4355 /wd4800 /wd4251 /wd4996 /wd4146 /wd4305")
add_definitions("/W3")

# Workaround for Visual Studio 2015 error C2338:
#   <hash_map> is deprecated and will be REMOVED. Please use <unordered_map>.
#   You can define _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS to acknowledge that you have received this warning.
add_definitions("/D_SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS")

include("protobuf-${PROTOBUF_VERSION_TAG}.targets")

#install(TARGETS libprotobuf libprotobuf-lite libprotoc DESTINATION lib)
#install(FILES ${LIBPROTOBUF_HEADERS} ${LIBPROTOBUF_LITE_HEADERS} ${LIBPROTOC_HEADERS} DESTINATION include)