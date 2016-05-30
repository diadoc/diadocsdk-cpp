include_directories("${CMAKE_CURRENT_SOURCE_DIR}/protos")

add_definitions(-D_SCL_SECURE_NO_WARNINGS)

set (DIADOC_API_HEADERS
	ApiException.h
	Certificate.h
	CertSystemStore.h
	CryptHelper.h
	DiadocApi.h
	DocumentFilter.h
	HttpConnect.h
	HttpException.h
	HttpRequest.h
	HttpSession.h
	resource.h
	stdafx.h
	StringHelper.h
	targetver.h
	TaskResult.h
	trace.h
)

set (DIADOC_API_SOURCES
	ApiException.cpp
	Certificate.cpp
	CertSystemStore.cpp
	CryptHelper.cpp
	DiadocApi.cpp
	dllmain.cpp
	DocumentFilter.cpp
	HttpConnect.cpp
	HttpException.cpp
	HttpRequest.cpp
	HttpSession.cpp
	stdafx.cpp
	StringHelper.cpp
	trace.cpp
)

set (PROTO_SOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/protos/")
file(GLOB_RECURSE PROTO_HEADERS "${PROTO_SOURCES_DIR}/*.pb.h")
file(GLOB_RECURSE PROTO_SOURCES "${PROTO_SOURCES_DIR}/*.pb.cc")

source_group(protos FILES ${PROTO_HEADERS} ${PROTO_SOURCES})

add_library(DiadocApi
	${PROTO_SOURCES}
	${PROTO_HEADERS}
	${DIADOC_API_HEADERS}
	${DIADOC_API_SOURCES}
)

target_link_libraries(DiadocApi
	libprotobuf
	libprotobuf-lite
	libprotoc
	crypt32.lib
	cryptui.lib
	version.lib
	winhttp.lib
)

include(precompiled-headers)
add_precompiled_header(DiadocApi "StdAfx.h" "StdAfx.cpp")
