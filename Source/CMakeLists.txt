add_subdirectory(Ellie)

add_executable(SimpleRayTracer Main.cpp)

target_compile_options(SimpleRayTracer PRIVATE -Wall -Wextra -pedantic -Werror)
target_compile_definitions(SimpleRayTracer PRIVATE UNIX)

target_link_libraries(SimpleRayTracer PUBLIC Ellie)
target_include_directories(SimpleRayTracer PUBLIC ${PROJECT_BINARY_DIR})
