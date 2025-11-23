cmake_minimum_required(VERSION 3.10)
project(Opal_Engine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(COPY ${CMAKE_SOURCE_DIR}/assets/
	DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets)

file(COPY ${CMAKE_SOURCE_DIR}/data/
	DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/data)

file(COPY ${CMAKE_SOURCE_DIR}/game_config.yaml
	DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_subdirectory(external/raylib)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} raylib)

target_include_directories(${PROJECT_NAME} PRIVATE src)

target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE
	external/raylib/src
	external/json/single_include
)
