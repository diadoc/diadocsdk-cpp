cmake_minimum_required(VERSION 2.8)

option(PROTOBUF_BUILD_SHARED_LIBS "Build the static library" OFF)
set(PROTOBUF_VERSION_TAG "2.6.1" CACHE STRING "Protobuf version tag from github")

set (GOOGLE_PROTOBUF_PATH "${CMAKE_CURRENT_SOURCE_DIR}/protobuf/")
set (GOOGLE_PROTOBUF_ARCHIVE_PATH "${CMAKE_CURRENT_BINARY_DIR}/protobuf-${PROTOBUF_VERSION_TAG}.tar.gz")
set (GOOGLE_PROTOBUF_EXTRACTED_ARCHIVE_PATH "${CMAKE_BINARY_DIR}/protobuf-${PROTOBUF_VERSION_TAG}/")

if (NOT EXISTS ${GOOGLE_PROTOBUF_PATH})
	if (NOT EXISTS ${GOOGLE_PROTOBUF_ARCHIVE_PATH})
		file(DOWNLOAD
			"https://github.com/google/protobuf/archive/v${PROTOBUF_VERSION_TAG}.tar.gz"
			${GOOGLE_PROTOBUF_ARCHIVE_PATH}
			SHOW_PROGRESS)
	endif()
	execute_process(COMMAND ${CMAKE_COMMAND} -E tar xvf ${GOOGLE_PROTOBUF_ARCHIVE_PATH})
	file(COPY ${GOOGLE_PROTOBUF_EXTRACTED_ARCHIVE_PATH} DESTINATION ${GOOGLE_PROTOBUF_PATH})
	if (NOT EXISTS ${GOOGLE_PROTOBUF_PATH})
		error("Please, check where protobuf was extracted")
	endif()
endif()

option(PROTOBUF_BUILD_SHARED_LIBS "Build the static library" OFF)
include_directories(
	"${GOOGLE_PROTOBUF_PATH}/src/"
	"${GOOGLE_PROTOBUF_PATH}/vsprojects/"
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