file(GLOB HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_library(Ellie SHARED ${HEADER_FILES} ${SOURCE_FILES})

target_compile_options(Ellie PRIVATE -Wall -Wextra -pedantic -Werror)
target_compile_definitions(Ellie PRIVATE UNIX)
target_precompile_headers(Ellie PUBLIC Pch.h)

target_include_directories(Ellie PUBLIC
	"${PROJECT_BINARY_DIR}"
	"$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>"
	"$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>"
	$<INSTALL_INTERFACE:include/SIMPLE_RAY_TRACER>)